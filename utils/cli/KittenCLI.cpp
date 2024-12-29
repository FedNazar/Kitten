/*
	Kitten Command-Line Utility
	(C) 2024 Nazar Fedorenko
	
	Licensed under the GNU GPLv3 license.
	
	This program is free software: you can redistribute it and/or modify it 
	under the terms of the GNU General Public License as published by the 
	Free Software Foundation, either version 3 of the License, or (at your option) 
	any later version.

	This program is distributed in the hope that it will be useful, but 
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
	or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
	for more details.

	You should have received a copy of the GNU General Public License along 
	with this program. If not, see <https://www.gnu.org/licenses/>.
	
	REMINDER: Kitten Library used by this utility is licensed under the
	BSD 2-Clause license.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>
#include <exception>
#include <stdexcept>

extern "C"
{
	#include "Kitten.h"
}

typedef struct CompressorArgs
{
	std::string inputFile;
	std::string outputFile;

	bool decompressionMode = false;

	bool customOffset;
	int compressionLevel;

	int minMatchLength = KITTEN_DEFAULT_MIN_MATCH_LENGTH;
	int memoryUsageLevel = KITTEN_DEFAULT_MEMORY_USAGE_LEVEL;
	int hashTableChainLimit = KITTEN_NO_HASH_TABLE_CHAIN_LIMIT;
} CompressorArgs;

void UsageInfo()
{
	std::cout << "Usage:\n"
			  << "kitten [main options] (input file name) [additional options]\n\n"
			  
			  << "Main options:\n"
			  << "-(1-22)           - compress file (1-22 - compression levels);\n"
			  << "-c(8192-16777215) - compress file with custom max.\n"
			  << "                    match offset value (custom compression level; 8192-16777215);\n"
			  << "-d                - decompress file\n\n"
			  
			  << "Additional options:\n"
			  << "-o, --output                 - set output file name;\n"
			  << "-l, --min-match-length       - set custom min. match length;\n"
			  << "                               higher value decreases compression time but\n"
			  << "                               degrades compression ratio (4-62; default - 5);\n"
			  << "-m, --memory-usage-level     - set memory usage level;\n"
			  << "                               higher value decreases compression time\n"
			  << "                               but uses more RAM (0-4; default - 3);\n"
			  << "-h, --hash-table-chain-limit - set limit for every hash table chain;\n"
			  << "                               lower value decreases compression time\n"
			  << "                               but degrades compression ratio;\n\n"
			  
			  << "Examples:\n"
			  << "kitten -1 input\n"
			  << "kitten -9 input -o output.kit\n"
			  << "kitten -22 input --output output.kit\n"
			  << "kitten -c20000 input\n"
			  << "kitten -d input.kit -o output\n"
			  << "kitten -1 input -m 2 -h 8 --output output.kit\n"
			  << "kitten -4 input -h 128 --min-match-length 6\n";
}

CompressorArgs ParseArguments(int argc, char** argv)
{
	CompressorArgs compressorArgs;

	if (std::strlen(argv[1]) < 1 && argv[1][0] != '-')
	{
		throw std::runtime_error("Too few arguments.");
	}

	compressorArgs.decompressionMode = argv[1][1] == 'd';
	compressorArgs.customOffset = argv[1][1] == 'c';
	
	compressorArgs.inputFile = argv[2];

	if (!compressorArgs.decompressionMode)
	{
		compressorArgs.compressionLevel = std::atoi(&argv[1][compressorArgs.customOffset ? 2 : 1]);

		if (!compressorArgs.customOffset && (compressorArgs.compressionLevel == 0 ||
			compressorArgs.compressionLevel > KITTEN_COMPRESSION_LEVELS))
		{
			throw std::runtime_error("Incorrect compression level.");
		}

		if (compressorArgs.customOffset && 
			(compressorArgs.compressionLevel < KITTEN_MIN_CUSTOM_MAX_OFFSET ||
			compressorArgs.compressionLevel > KITTEN_MAX_CUSTOM_MAX_OFFSET))
		{
			throw std::runtime_error("Incorrect max. offset value.");
		}
		
		// Default output file name
		compressorArgs.outputFile = compressorArgs.inputFile + ".kit";
	}
	else
	{
		// Default output file name
		
		size_t fileExtBegin = compressorArgs.inputFile.rfind('.');
		if (fileExtBegin == -1 || fileExtBegin == 0)
		{
			compressorArgs.outputFile = compressorArgs.inputFile + "_dec";
		}
		else
		{
			compressorArgs.outputFile = compressorArgs.inputFile.substr(0, fileExtBegin);
		}
	}

	// Parse additional argument
	int curArg = 3;
	while (curArg < argc)
	{
		if (!std::strcmp("--min-match-length", argv[curArg]) ||
			!std::strcmp("-l", argv[curArg]))
		{
			if (curArg == argc - 1)
			{
				throw std::runtime_error("Min. match length is not specified.");
			}

			compressorArgs.minMatchLength = std::atoi(argv[curArg + 1]);

			if (compressorArgs.minMatchLength < KITTEN_MIN_CUSTOM_MATCH_LENGTH ||
				compressorArgs.minMatchLength > KITTEN_MAX_CUSTOM_MATCH_LENGTH)
			{
				throw std::runtime_error("Incorrect min. match length.");
			}
		}
		else if (!std::strcmp("--memory-usage-level", argv[curArg]) ||
			!std::strcmp("-m", argv[curArg]))
		{
			if (curArg == argc - 1)
			{
				throw std::runtime_error("Memory usage level is not specified.");
			}

			compressorArgs.memoryUsageLevel = std::atoi(argv[curArg + 1]);

			if (compressorArgs.memoryUsageLevel >= KITTEN_MEMORY_USAGE_LEVELS ||
				compressorArgs.memoryUsageLevel < 0)
			{
				throw std::runtime_error("Incorrect memory usage level.");
			}
		}
		else if (!std::strcmp("--hash-table-chain-limit", argv[curArg]) ||
			!std::strcmp("-h", argv[curArg]))
		{
			if (curArg == argc - 1)
			{
				throw std::runtime_error("Hash table chain limit is not specified.");
			}

			compressorArgs.hashTableChainLimit = std::atoi(argv[curArg + 1]);

			if (compressorArgs.hashTableChainLimit < 1 ||
				compressorArgs.hashTableChainLimit > KITTEN_MAX_CUSTOM_MAX_OFFSET)
			{
				throw std::runtime_error("Incorrect hash table chain limit.");
			}
		}
		else if (!std::strcmp("--output", argv[curArg]) ||
			!std::strcmp("-o", argv[curArg]))
		{
			if (curArg == argc - 1)
			{
				throw std::runtime_error("Output file name is not specified.");
			}

			compressorArgs.outputFile = argv[curArg + 1];
		}
		else
		{
			std::string errorStr = std::string(argv[curArg]) + " - unknown parameter.";
			throw std::runtime_error(errorStr.c_str());
		}

		curArg += 2;
	}

	return compressorArgs;
}

bool CheckForErrors(uint64_t result)
{
	switch (result)
	{
		case KITTEN_INCOMPRESSIBLE_DATA_ERROR:
			std::cerr << "Incompressible data.\n";
			return true;
		case KITTEN_DECOMPRESSION_ERROR:
			std::cerr << "Corrupted data.\n";
			return true;
		case KITTEN_MEMORY_ERROR:
			std::cerr << "Failed to allocate memory.\n";
			return true;
		case KITTEN_PARAMETER_ERROR:
			std::cerr << "Incorrect parameters.\n";
			return true;
		case KITTEN_SIGNATURE_ERROR:
			std::cerr << "This file is not a Kitten-compressed file.\n";
			return true;
		case KITTEN_TOO_SMALL_DATA_ERROR:
			std::cerr << "Data is too small to compress.\n";
			return true;
		case KITTEN_FILE_READ_ERROR:
			std::cerr << "Can't read the file.\n";
			return true;
		case KITTEN_FILE_WRITE_ERROR:
			std::cerr << "Can't write to the file.\n";
			return true;
		default:
			return false;
	}
}

bool OverwriteConfirmation(std::string fileName)
{
	if (!std::filesystem::exists(fileName))
		return true;

	std::string input;
	std::cout << fileName << " already exists. Overwrite? (y/N) ";
	std::cin >> input;

	bool result = (input == "y" || input == "Y");
	if (!result) std::cerr << "Operation cancelled.\n";

	return result;
}

int Decompress(CompressorArgs* compressorArgs)
{
	if (!OverwriteConfirmation(compressorArgs->outputFile))
		return -1;

	std::cout << "Loading and decompressing...\n\n";

	uint64_t result = KittenDecompressFile(compressorArgs->inputFile.c_str(),
		compressorArgs->outputFile.c_str());

	if (CheckForErrors(result))
	{
		return -1;
	}

	std::cout << "Decompressed to " << result << " bytes.\n";

	return 0;
}

int Compress(CompressorArgs* compressorArgs)
{
	if (!OverwriteConfirmation(compressorArgs->outputFile))
		return -1;

	std::cout << "Loading and compressing...\n\n";

	uint64_t result = KittenCompressFile(compressorArgs->inputFile.c_str(),
		compressorArgs->outputFile.c_str(),
		compressorArgs->compressionLevel,
		compressorArgs->memoryUsageLevel,
		compressorArgs->minMatchLength,
		compressorArgs->hashTableChainLimit);

	if (CheckForErrors(result))
	{
		return -1;
	}

	std::cout << "Compressed to " << result << " bytes.\n";

	return 0;
}

int main(int argc, char** argv)
{
	std::cout << "Kitten Command-Line Utility\n"
			  << "Version " << KITTEN_VERSION << '\n'
			  << "(C) 2024 Nazar Fedorenko\n\n";
			  
	if (argc < 3)
	{
		UsageInfo();
		return 0;
	}

	CompressorArgs compressorArgs;
	try
	{
		compressorArgs = ParseArguments(argc, argv);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	if (compressorArgs.decompressionMode)
		return Decompress(&compressorArgs);

	return Compress(&compressorArgs);
}