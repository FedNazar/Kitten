# Kitten

LZSS-based lossless data compression algorithm, aimed at **fast decompression speeds** (approx. 3 GB/s on one CPU core)
and **better compression ratios than LZ4HC**, QuickLZ, FastLZ and other decompression speed oriented
algorithms (see "Benchmarks" section for more information). However, the downside of this technology 
is its very **slow compression speed**. 

This algorithm is suitable for use in video games because the developer has to compress game assets 
once and fast decompression allows for fast loading times for the end-user.

Kitten Library is written in C and licensed under the BSD 2-Clause license.

## Benchmarks

Kitten was tested using the [fork](https://github.com/FedNazar/lzbench) of [lzbench](https://github.com/inikep/lzbench) 1.8
with Kitten support on the system with AMD Ryzen 7 5800H CPU at 4.4 GHz, 16 GB of RAM and
Windows 11 23H2 64-bit on one CPU core.

[Silesia dataset](https://sun.aei.polsl.pl//~sdeor/index.php?page=silesia) (compiler: LLVM Clang x86_64 15.0.7):

| Compressor name         | Compression| Decompress.| Compr. size | Ratio | Filename |
| ---------------         | -----------| -----------| ----------- | ----- | -------- |
| memcpy                  | 17053 MB/s | 16980 MB/s |   211948032 |100.00 | silesia.tar|
| **kitten 1.0 -1**       |  10.8 MB/s |  3547 MB/s |    83186237 | 39.25 | silesia.tar|
| **kitten 1.0 -2**       |  5.18 MB/s |  3586 MB/s |    81421699 | 38.42 | silesia.tar|
| **kitten 1.0 -4**       |  1.03 MB/s |  3446 MB/s |    77548039 | 36.59 | silesia.tar|
| **kitten 1.0 -6**       |  0.59 MB/s |  3436 MB/s |    75621570 | 35.68 | silesia.tar|
| **kitten 1.0 -9**       |  0.31 MB/s |  3398 MB/s |    74225715 | 35.02 | silesia.tar|
| **kitten 1.0 -12**      |  0.17 MB/s |  3252 MB/s |    73057265 | 34.47 | silesia.tar|
| **kitten 1.0 -15**      |  0.13 MB/s |  3005 MB/s |    72400016 | 34.16 | silesia.tar|
| **kitten 1.0 -18**      |  0.85 MB/s |  2737 MB/s |    72045341 | 33.99 | silesia.tar|
| **kitten 1.0 -22**      |  0.31 MB/s |  2528 MB/s |    71745154 | 33.85 | silesia.tar|
| zlib 1.2.11 -1          |   137 MB/s |   436 MB/s |    77260163 | 36.45 | silesia.tar|
| zlib 1.2.11 -3          |  89.4 MB/s |   466 MB/s |    72968852 | 34.43 | silesia.tar|
| zlib 1.2.11 -5          |  56.1 MB/s |   459 MB/s |    69163221 | 32.63 | silesia.tar|
| zlib 1.2.11 -9          |  15.1 MB/s |   473 MB/s |    67643840 | 31.92 | silesia.tar|
| lz4 1.9.3               |   786 MB/s |  4391 MB/s |   100880833 | 47.60 | silesia.tar|
| lz4hc 1.9.3 -1          |   139 MB/s |  3954 MB/s |    83803850 | 39.54 | silesia.tar|
| lz4hc 1.9.3 -5          |  76.4 MB/s |  4181 MB/s |    78895423 | 37.22 | silesia.tar|
| lz4hc 1.9.3 -9          |  38.0 MB/s |  4266 MB/s |    77884544 | 36.75 | silesia.tar|
| lz4hc 1.9.3 -12         |  14.0 MB/s |  4329 MB/s |    77262717 | 36.45 | silesia.tar|
| zstd 1.5.5 -1           |   534 MB/s |  1481 MB/s |    73425052 | 34.64 | silesia.tar|
| zstd 1.5.5 -2           |   424 MB/s |  1383 MB/s |    69497626 | 32.79 | silesia.tar|
| zstd 1.5.5 -3           |   290 MB/s |  1355 MB/s |    66525034 | 31.39 | silesia.tar|
| zstd 1.5.5 -4           |   261 MB/s |  1330 MB/s |    65324976 | 30.82 | silesia.tar|
| zstd 1.5.5 -5           |   160 MB/s |  1338 MB/s |    63041116 | 29.74 | silesia.tar|
| snappy 1.1.10           |   867 MB/s |  2679 MB/s |   102168085 | 48.20 | silesia.tar|
| fastlz 0.5.0 -1         |   391 MB/s |   860 MB/s |   104628049 | 49.36 | silesia.tar|
| fastlz 0.5.0 -2         |   401 MB/s |   843 MB/s |   100906049 | 47.61 | silesia.tar|
| lzo1 2.10 -1            |   341 MB/s |   868 MB/s |   106474144 | 50.24 | silesia.tar|
| lzo1 2.10 -99           |   153 MB/s |   920 MB/s |    94946370 | 44.80 | silesia.tar|
| quicklz 1.5.0 -1        |   594 MB/s |   615 MB/s |    94723606 | 44.69 | silesia.tar|
| quicklz 1.5.0 -2        |   326 MB/s |   576 MB/s |    84564074 | 39.90 | silesia.tar|
| quicklz 1.5.0 -3        |  80.3 MB/s |  1075 MB/s |    81821336 | 38.60 | silesia.tar|

[enwik8 dataset](https://mattmahoney.net/dc/textdata.html) (compiler: LLVM Clang x86_64 15.0.7):

| Compressor name         | Compression| Decompress.| Compr. size | Ratio | Filename |
| ---------------         | -----------| -----------| ----------- | ----- | -------- |
| memcpy                  | 17640 MB/s | 17730 MB/s |   100000000 |100.00 | enwik8|
| **kitten 1.0 -1**       |  22.9 MB/s |  2977 MB/s |    45387178 | 45.39 | enwik8|
| **kitten 1.0 -2**       |  14.6 MB/s |  3063 MB/s |    44013527 | 44.01 | enwik8|
| **kitten 1.0 -4**       |  3.71 MB/s |  3125 MB/s |    40689677 | 40.69 | enwik8|
| **kitten 1.0 -6**       |  1.39 MB/s |  3132 MB/s |    38882387 | 38.88 | enwik8|
| **kitten 1.0 -9**       |  0.60 MB/s |  3138 MB/s |    37411868 | 37.41 | enwik8|
| **kitten 1.0 -12**      |  0.30 MB/s |  2834 MB/s |    36021480 | 36.02 | enwik8|
| **kitten 1.0 -15**      |  0.19 MB/s |  2237 MB/s |    34976775 | 34.98 | enwik8|
| **kitten 1.0 -18**      |  0.14 MB/s |  1760 MB/s |    34290304 | 34.29 | enwik8|
| **kitten 1.0 -22**      |  0.10 MB/s |  1360 MB/s |    33610190 | 33.61 | enwik8|
| zlib 1.2.11 -1          |   118 MB/s |   362 MB/s |    42298774 | 42.30 | enwik8|
| zlib 1.2.11 -3          |  71.3 MB/s |   382 MB/s |    39542363 | 39.54 | enwik8|
| zlib 1.2.11 -5          |  42.2 MB/s |   368 MB/s |    36879092 | 36.88 | enwik8|
| zlib 1.2.11 -9          |  22.2 MB/s |   372 MB/s |    36475792 | 36.48 | enwik8|
| lz4 1.9.3               |   570 MB/s |  3940 MB/s |    57262281 | 57.26 | enwik8|
| lz4hc 1.9.3 -1          |   114 MB/s |  3307 MB/s |    45323416 | 45.32 | enwik8|
| lz4hc 1.9.3 -5          |  60.0 MB/s |  3479 MB/s |    42528579 | 42.53 | enwik8|
| lz4hc 1.9.3 -9          |  37.4 MB/s |  3506 MB/s |    42203094 | 42.20 | enwik8|
| lz4hc 1.9.3 -12         |  20.5 MB/s |  3430 MB/s |    41913140 | 41.91 | enwik8|
| zstd 1.5.5 -1           |   392 MB/s |  1322 MB/s |    40667563 | 40.67 | enwik8|
| zstd 1.5.5 -2           |   292 MB/s |  1174 MB/s |    37332782 | 37.33 | enwik8|
| zstd 1.5.5 -3           |   212 MB/s |  1120 MB/s |    35461800 | 35.46 | enwik8|
| zstd 1.5.5 -4           |   192 MB/s |  1078 MB/s |    34754903 | 34.75 | enwik8|
| zstd 1.5.5 -5           |   128 MB/s |  1083 MB/s |    33702880 | 33.70 | enwik8|
| snappy 1.1.10           |   572 MB/s |  2063 MB/s |    56555035 | 56.56 | enwik8|
| fastlz 0.5.0 -1         |   311 MB/s |   602 MB/s |    55239233 | 55.24 | enwik8|
| fastlz 0.5.0 -2         |   289 MB/s |   586 MB/s |    54163013 | 54.16 | enwik8|
| lzo1 2.10 -1            |   281 MB/s |   558 MB/s |    57975532 | 57.98 | enwik8|
| lzo1 2.10 -99           |   134 MB/s |   613 MB/s |    49986864 | 49.99 | enwik8|
| quicklz 1.5.0 -1        |   398 MB/s |   562 MB/s |    52334371 | 52.33 | enwik8|
| quicklz 1.5.0 -2        |   226 MB/s |   556 MB/s |    45883075 | 45.88 | enwik8|
| quicklz 1.5.0 -3        |  61.1 MB/s |   796 MB/s |    44789793 | 44.79 | enwik8|

[Silesia dataset](https://sun.aei.polsl.pl//~sdeor/index.php?page=silesia) (compiler: GCC 14.2.0):

| Compressor name         | Compression| Decompress.| Compr. size | Ratio | Filename |
| ---------------         | -----------| -----------| ----------- | ----- | -------- |
| memcpy                  | 15767 MB/s | 15800 MB/s |   211948032 |100.00 | silesia.tar|
| **kitten 1.0 -1**       |  11.3 MB/s |  3132 MB/s |    83186237 | 39.25 | silesia.tar|
| **kitten 1.0 -2**       |  6.72 MB/s |  3210 MB/s |    81421699 | 38.42 | silesia.tar|
| **kitten 1.0 -4**       |  1.50 MB/s |  3287 MB/s |    77548039 | 36.59 | silesia.tar|
| **kitten 1.0 -6**       |  0.60 MB/s |  3241 MB/s |    75621570 | 35.68 | silesia.tar|
| **kitten 1.0 -9**       |  0.31 MB/s |  3211 MB/s |    74225715 | 35.02 | silesia.tar|
| **kitten 1.0 -12**      |  0.18 MB/s |  3113 MB/s |    73057265 | 34.47 | silesia.tar|
| **kitten 1.0 -15**      |  0.13 MB/s |  2934 MB/s |    72400016 | 34.16 | silesia.tar|
| **kitten 1.0 -18**      |  0.84 MB/s |  2732 MB/s |    72045341 | 33.99 | silesia.tar|
| **kitten 1.0 -22**      |  0.31 MB/s |  2527 MB/s |    71745154 | 33.85 | silesia.tar|
| zlib 1.2.11 -1          |   130 MB/s |   441 MB/s |    77260163 | 36.45 | silesia.tar|
| zlib 1.2.11 -3          |  86.6 MB/s |   471 MB/s |    72968852 | 34.43 | silesia.tar|
| zlib 1.2.11 -5          |  56.1 MB/s |   458 MB/s |    69163221 | 32.63 | silesia.tar|
| zlib 1.2.11 -9          |  15.0 MB/s |   472 MB/s |    67643840 | 31.92 | silesia.tar|
| lz4 1.9.3               |   801 MB/s |  4616 MB/s |   100880833 | 47.60 | silesia.tar|
| lz4hc 1.9.3 -1          |   149 MB/s |  4191 MB/s |    83803850 | 39.54 | silesia.tar|
| lz4hc 1.9.3 -5          |  82.8 MB/s |  4425 MB/s |    78895423 | 37.22 | silesia.tar|
| lz4hc 1.9.3 -9          |  41.8 MB/s |  4510 MB/s |    77884544 | 36.75 | silesia.tar|
| lz4hc 1.9.3 -12         |  15.0 MB/s |  4602 MB/s |    77262717 | 36.45 | silesia.tar|
| zstd 1.5.5 -1           |   544 MB/s |  1662 MB/s |    73425052 | 34.64 | silesia.tar|
| zstd 1.5.5 -2           |   421 MB/s |  1561 MB/s |    69497626 | 32.79 | silesia.tar|
| zstd 1.5.5 -3           |   319 MB/s |  1529 MB/s |    66525034 | 31.39 | silesia.tar|
| zstd 1.5.5 -4           |   280 MB/s |  1493 MB/s |    65324976 | 30.82 | silesia.tar|
| zstd 1.5.5 -5           |   157 MB/s |  1508 MB/s |    63041116 | 29.74 | silesia.tar|
| snappy 1.1.10           |   577 MB/s |  1634 MB/s |   102168085 | 48.20 | silesia.tar|
| fastlz 0.5.0 -1         |   398 MB/s |   905 MB/s |   104628049 | 49.36 | silesia.tar|
| fastlz 0.5.0 -2         |   412 MB/s |   900 MB/s |   100906049 | 47.61 | silesia.tar|
| lzo1 2.10 -1            |   340 MB/s |   892 MB/s |   106474144 | 50.24 | silesia.tar|
| lzo1 2.10 -99           |   150 MB/s |   944 MB/s |    94946370 | 44.80 | silesia.tar|
| quicklz 1.5.0 -1        |   631 MB/s |   624 MB/s |    94723606 | 44.69 | silesia.tar|
| quicklz 1.5.0 -2        |   317 MB/s |   629 MB/s |    84564074 | 39.90 | silesia.tar|
| quicklz 1.5.0 -3        |  84.1 MB/s |  1163 MB/s |    81821336 | 38.60 | silesia.tar|

[enwik8 dataset](https://mattmahoney.net/dc/textdata.html) (compiler: GCC 14.2.0):

| Compressor name         | Compression| Decompress.| Compr. size | Ratio | Filename |
| ---------------         | -----------| -----------| ----------- | ----- | -------- |
| memcpy                  | 15797 MB/s | 15890 MB/s |   100000000 |100.00 | enwik8|
| **kitten 1.0 -1**       |  25.7 MB/s |  2296 MB/s |    45387178 | 45.39 | enwik8|
| **kitten 1.0 -2**       |  16.6 MB/s |  2492 MB/s |    44013527 | 44.01 | enwik8|
| **kitten 1.0 -4**       |  4.05 MB/s |  2834 MB/s |    40689677 | 40.69 | enwik8|
| **kitten 1.0 -6**       |  1.45 MB/s |  2965 MB/s |    38882387 | 38.88 | enwik8|
| **kitten 1.0 -9**       |  0.62 MB/s |  3041 MB/s |    37411868 | 37.41 | enwik8|
| **kitten 1.0 -12**      |  0.29 MB/s |  3005 MB/s |    36021480 | 36.02 | enwik8|
| **kitten 1.0 -15**      |  0.18 MB/s |  2282 MB/s |    34976775 | 34.98 | enwik8|
| **kitten 1.0 -18**      |  0.13 MB/s |  1847 MB/s |    34290304 | 34.29 | enwik8|
| **kitten 1.0 -22**      |  0.10 MB/s |  1452 MB/s |    33610190 | 33.61 | enwik8|
| zlib 1.2.11 -1          |   113 MB/s |   367 MB/s |    42298774 | 42.30 | enwik8|
| zlib 1.2.11 -3          |  69.6 MB/s |   387 MB/s |    39542363 | 39.54 | enwik8|
| zlib 1.2.11 -5          |  42.3 MB/s |   365 MB/s |    36879092 | 36.88 | enwik8|
| zlib 1.2.11 -9          |  22.4 MB/s |   370 MB/s |    36475792 | 36.48 | enwik8|
| lz4 1.9.3               |   581 MB/s |  4308 MB/s |    57262281 | 57.26 | enwik8|
| lz4hc 1.9.3 -1          |   121 MB/s |  3608 MB/s |    45323416 | 45.32 | enwik8|
| lz4hc 1.9.3 -5          |  63.5 MB/s |  3777 MB/s |    42528579 | 42.53 | enwik8|
| lz4hc 1.9.3 -9          |  39.7 MB/s |  3805 MB/s |    42203094 | 42.20 | enwik8|
| lz4hc 1.9.3 -12         |  20.5 MB/s |  3735 MB/s |    41913140 | 41.91 | enwik8|
| zstd 1.5.5 -1           |   401 MB/s |  1524 MB/s |    40667563 | 40.67 | enwik8|
| zstd 1.5.5 -2           |   288 MB/s |  1373 MB/s |    37332782 | 37.33 | enwik8|
| zstd 1.5.5 -3           |   226 MB/s |  1309 MB/s |    35461800 | 35.46 | enwik8|
| zstd 1.5.5 -4           |   199 MB/s |  1234 MB/s |    34754903 | 34.75 | enwik8|
| zstd 1.5.5 -5           |   125 MB/s |  1240 MB/s |    33702880 | 33.70 | enwik8|
| snappy 1.1.10           |   365 MB/s |  1114 MB/s |    56555035 | 56.56 | enwik8|
| fastlz 0.5.0 -1         |   317 MB/s |   629 MB/s |    55239233 | 55.24 | enwik8|
| fastlz 0.5.0 -2         |   297 MB/s |   619 MB/s |    54163013 | 54.16 | enwik8|
| lzo1 2.10 -1            |   281 MB/s |   562 MB/s |    57975532 | 57.98 | enwik8|
| lzo1 2.10 -99           |   131 MB/s |   611 MB/s |    49986864 | 49.99 | enwik8|
| quicklz 1.5.0 -1        |   420 MB/s |   599 MB/s |    52334371 | 52.33 | enwik8|
| quicklz 1.5.0 -2        |   221 MB/s |   603 MB/s |    45883075 | 45.88 | enwik8|
| quicklz 1.5.0 -3        |  63.1 MB/s |   835 MB/s |    44789793 | 44.79 | enwik8|

## Library usage examples in C

Library source code consists of 2 files (Kitten.c, Kitten.h) located in the lib directory
of this repository.

Compress data from an input buffer and write it to an output buffer:

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include "Kitten.h"

int main()
{
	uint64_t inDataSize = 100000; // Example size
	unsigned char* inBuffer = (unsigned char*)malloc(KittenBufferSize(inDataSize));
	
	if (inBuffer == NULL) return -1;
	
	// Code to put your data into the buffer goes here
	
	unsigned char* outBuffer = (unsigned char*)malloc(KittenBufferSize(inDataSize));
	
	if (outBuffer == NULL)
	{
		free(inBuffer);
		return -1;
	}
	
	uint64_t outDataSize = KittenCompress(inBuffer, outBuffer, inDataSize, 
		4, // Compression level (1-22)
		KITTEN_DEFAULT_MEMORY_USAGE_LEVEL, // (0-4; default - 3)
		KITTEN_DEFAULT_MIN_MATCH_LENGTH, // (4-62; default - 5)
		KITTEN_NO_HASH_TABLE_CHAIN_LIMIT); // (0-16777215; default - 0)
	
	free(inBuffer);
	
	// Handle errors
	
	switch (outDataSize)
	{
		case KITTEN_INCOMPRESSIBLE_DATA_ERROR:
			printf("Incompressible data!\n");
			free(outBuffer);
			return -1;
		case KITTEN_PARAMETER_ERROR:
			printf("Wrong parameters!\n");
			free(outBuffer);
			return -1;
		case KITTEN_TOO_SMALL_DATA_ERROR:
			printf("Input data is too small to compress!\n");
			free(outBuffer);
			return -1;
	}
	
	free(outBuffer);
	
	return 0;
}
```

Decompress data from an input buffer and write it to an output buffer:

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include "Kitten.h"

int main()
{
	// Example sizes
	uint64_t inDataSize = 50000;
	uint64_t outDataSize = 100000;
	
	unsigned char* inBuffer = (unsigned char*)malloc(KittenBufferSize(inDataSize));
	
	if (inBuffer == NULL) return -1;
	
	// Code to load your compressed data into the buffer goes here
	
	unsigned char* outBuffer = (unsigned char*)malloc(KittenBufferSize(outDataSize));
	
	if (outBuffer == NULL)
	{
		free(inBuffer);
		return -1;
	}
	
	uint64_t decompressedSize = KittenDecompress(inBuffer, outBuffer, 
		inDataSize, outDataSize);
		
	free(inBuffer);
		
	if (decompressedSize == KITTEN_DECOMPRESSION_ERROR)
	{
		printf("Decompression error!\n");
		free(outBuffer);
		return -1;
	}
	
	free(outBuffer);
	
	return 0;
}
```

Compress file:

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include "Kitten.h"

int main()
{
	uint64_t compressedSize = KittenCompressFile("input_file",
		"output_file.kit",
		4, // Compression level (1-22)
		KITTEN_DEFAULT_MEMORY_USAGE_LEVEL, // (0-4; default - 3)
		KITTEN_DEFAULT_MIN_MATCH_LENGTH, // (4-62; default - 5)
		KITTEN_NO_HASH_TABLE_CHAIN_LIMIT); // (0-16777215; default - 0)
		
	// Handle errors
	
	switch (compressedSize)
	{
		case KITTEN_MEMORY_ERROR:
			printf("Failed to allocate memory!\n);
			return -1;
		case KITTEN_FILE_READ_ERROR:
			printf("Failed to read the input file!\n");
			return -1;
		case KITTEN_FILE_WRITE_ERROR:
			printf("Failed to write to the output file!\n");
			return -1;
		case KITTEN_INCOMPRESSIBLE_DATA_ERROR:
			printf("Incompressible data!\n");
			return -1;
		case KITTEN_PARAMETER_ERROR:
			printf("Wrong parameters!\n");
			return -1;
		case KITTEN_TOO_SMALL_DATA_ERROR:
			printf("Input data is too small to compress!\n");
			return -1;
	}

	return 0;
}
```

Decompress file:

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include "Kitten.h"

int main()
{
	uint64_t decompressedSize = KittenDecompressFile("input_file.kit", "output_file");
	
	// Handle errors
	
	switch (decompressedSize)
	{
		case KITTEN_MEMORY_ERROR:
			printf("Failed to allocate memory!\n);
			return -1;
		case KITTEN_FILE_READ_ERROR:
			printf("Failed to read the input file!\n");
			return -1;
		case KITTEN_SIGNATURE_ERROR:
			printf("This file is not a Kitten-compressed file!\n");
			return -1;
		case KITTEN_FILE_WRITE_ERROR:
			printf("Failed to write to the output file!\n");
			return -1;
		case KITTEN_DECOMPRESSION_ERROR:
			printf("Decompression error!\n");
			return -1;
	}

	return 0;
}
```

Decompress file into memory (to a buffer):

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include "Kitten.h"

int main()
{
	uint64_t decompressedSize;
	
	// This function will allocate decompressed data 
	// buffer internally and return a pointer to it
	unsigned size* decompressedData = KittenDecompressFileToMemory(
		"input_file.kit", &decompressedSize);
		
	// Handle errors
	
	if (decompressedData == NULL)
	{
		switch (decompressedSize)
		{
			case KITTEN_MEMORY_ERROR:
				printf("Failed to allocate memory!\n);
				return -1;
			case KITTEN_FILE_READ_ERROR:
				printf("Failed to read the input file!\n");
				return -1;
			case KITTEN_SIGNATURE_ERROR:
				printf("This file is not a Kitten-compressed file!\n");
				return -1;
			case KITTEN_DECOMPRESSION_ERROR:
				printf("Decompression error!\n");
				return -1;
		}
	}

	KittenDeallocate(decompressedData); // You can use free() too
	
	return 0;
}
```

## Command-Line Utility

This repository contains the source code for the Kitten Command-Line Utility (utils/cli).
This utility can be used to compress and decompress files. 

You can either build this tool yourself or download the binaries from the "Releases" section.
To get usage information, run this utility normally (`./kitten`) or type (`./kitten --help`).

To build this tool, change your directory to utils/cli and run `make` command. You can
modify the Makefile to use GCC instead of Clang:

```makefile
CC = gcc
CXX = g++
```

You can also enable AVX support by uncommenting this line:

```makefile
#CFLAGS += -mavx
```

## License

Kitten Library is licensed under the BSD 2-Clause license. Read lib/LICENSE file for more details.
(C) 2024 [Nazar Fedorenko](https://github.com/FedNazar/).

Kitten Command-Line Utility is licensed under the GNU GPLv3 license. Read utils/cli/LICENSE for more details.
(C) 2024 [Nazar Fedorenko](https://github.com/FedNazar/).