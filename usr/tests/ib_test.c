/*
 * Copyright (c) 2017, Annika Wierichs, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the University nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/*#include <verbs.h>	// GEHT, brauche ich aber nicht?*/

#include <hermit/ibv.h>	// Geht per cmake copy workaround

#define N	255

static void test_handler(int s)
{
	printf("Receive signal with number %d\n", s);
}

int main(int argc, char** argv)
{
	int i, random;
	FILE* file;

	// ---------------------------------------------------------------------------

	/*struct ibv_device **dev_list;*/
	/*int num_devices;*/

	printf("before get dev list.\n");

	/*dev_list = h_ibv_get_device_list(&num_devices);*/
	/*printf("after get dev list.\n");*/

	/*printf("char name: %s", dev_list[0]->name);*/

	/*if (!dev_list) {*/
		/*perror("Failed to get IB devices list");*/
		/*return 1;*/
	/*}*/
	/*printf("after dev list check.\n");*/

	/*const char* dev_name = h_ibv_get_device_name(dev_list[0]);*/
	/*printf("after get device name.\n");*/

	/*if (!dev_name) {*/
		/*perror("Failed to get devices name");*/
		/*return 1;*/
	/*}*/

	/*printf("Device: %s", dev_name);*/
	/*printf("\nafter get dev name.\n");*/

	// ---------------------------------------------------------------------------

	// register test handler
	signal(SIGUSR1, test_handler);

	printf("Hello World!!!\n");
	//for(i=0; environ[i]; i++)
	//	printf("environ[%d] = %s\n", i, environ[i]);
	for(i=0; i<argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);

	raise(SIGUSR1);

	file = fopen("/etc/hostname", "r");
	if (file)
	{
		char fname[N] = "";

		fscanf(file, "%s", fname);
		printf("Hostname: %s\n", fname);
		fclose(file);
	} else fprintf(stderr, "Unable to open file /etc/hostname\n");

	file = fopen("/tmp/test.txt", "w");
	if (file)
	{
		fprintf(file, "Hello World!!!\n");
		fclose(file);
	} else fprintf(stderr, "Unable to open file /tmp/test.txt\n");

	return 0;
}
