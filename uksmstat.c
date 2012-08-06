/*
    uksmstat — small tool to show UKSM statistics
    Copyright © 2012 Oleksandr Natalenko aka post-factum <pfactum@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int opts = 0, unshared = 0, shared = 1, kilobytes = 0, megabytes = 1, verbose = 0;
	while ((opts = getopt(argc, argv, "uskmv")) != -1)
	{
		switch (opts)
		{
			case 'u':
				unshared = 1;
				break;
			case 's':
				shared = 1;
				break;
			case 'k':
				kilobytes = 1;
				break;
			case 'm':
				megabytes = 1;
				break;
			case 'v':
				verbose++;
				break;
			default:
				fprintf(stderr, "Unknown option: %c\n", opts);
				exit(1);
				break;
		}
	}

	long page_size = sysconf(_SC_PAGESIZE);
	if (unshared == 1)
	{
		FILE *f = fopen("/sys/kernel/mm/uksm/pages_unshared", "r");
		long pages_unshared;
		fscanf(f, "%ld", &pages_unshared);
		fclose(f);
		if (verbose == 0)
		{
			if (kilobytes == 1)
				fprintf(stdout, "%ld\n", page_size * pages_unshared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "%ld\n", page_size * pages_unshared / (1024 * 1024));
		} else if (verbose == 1)
		{
			if (kilobytes == 1)
				fprintf(stdout, "%ld KiB\n", page_size * pages_unshared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "%ld MiB\n", page_size * pages_unshared / (1024 * 1024));
		} else if (verbose == 2)
		{
			if (kilobytes == 1)
				fprintf(stdout, "Unshared pages: %ld KiB\n", page_size * pages_unshared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "Unshared pages: %ld MiB\n", page_size * pages_unshared / (1024 * 1024));
		}
	}
	if (shared == 1)
	{
		FILE *f = fopen("/sys/kernel/mm/uksm/pages_sharing", "r");
		long pages_shared;
		fscanf(f, "%ld", &pages_shared);
		fclose(f);
		if (verbose == 0)
		{
			if (kilobytes == 1)
				fprintf(stdout, "%ld\n", page_size * pages_shared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "%ld\n", page_size * pages_shared / (1024 * 1024));
		} else if (verbose == 1)
		{
			if (kilobytes == 1)
				fprintf(stdout, "%ld KiB\n", page_size * pages_shared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "%ld MiB\n", page_size * pages_shared / (1024 * 1024));
		} else if (verbose == 2)
		{
			if (kilobytes == 1)
				fprintf(stdout, "Shared pages: %ld KiB\n", page_size * pages_shared / 1024);
			else if (megabytes == 1)
				fprintf(stdout, "Shared pages: %ld MiB\n", page_size * pages_shared / (1024 * 1024));
		}
	}
	return 0;
}

