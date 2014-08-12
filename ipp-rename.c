/*-
 * Copyright (c) 2014 Romain Tartière <romain@blogreen.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <cups/cups.h>

#if CUPS_VERSION_MAJOR == 1 && CUPS_VERSION_MINOR < 6
#  define ippGetString(attr, a, b) attr->values[0].string.value
#endif

int
main (int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
	ipp_t *ipp = ippNew ();

	int fd = open (argv[i], O_RDONLY);
	if (fd < 0)
	    err (EXIT_FAILURE, "open");

	ipp_state_t res = ippReadFile(fd, ipp);
	if (res != IPP_DATA)
	    err (EXIT_FAILURE, "ippReadFile : %d", res);

	close (fd);

	ipp_attribute_t *attr;
	attr = ippFindAttribute (ipp, "job-name", IPP_TAG_NAME);

	const char *old_name = ippGetString (attr, 0, NULL);

	printf ("job %s title is: \"%s\"\n", argv[i], old_name);
	printf ("remame job [yN] ");

	char buffer[BUFSIZ];
	fgets (buffer, BUFSIZ, stdin);

	if (buffer[0] == 'y' || buffer[0] == 'Y') {
	    printf ("New job name: ");
	    fgets (buffer, BUFSIZ, stdin);
	    if (buffer[strlen (buffer) - 1] == '\n')
		buffer[strlen (buffer) - 1] = '\0';

	    ippDeleteAttribute (ipp, attr);

	    ippAddString (ipp, IPP_TAG_JOB, IPP_TAG_NAME, "job-name", NULL, buffer);

	    if ((fd = open (argv[i], O_WRONLY | O_CREAT)) < 0)
		err (EXIT_FAILURE, "open");
	    ippWriteFile (fd, ipp);
	    close (fd);
	}

	ippDelete (ipp);
    }

    exit (EXIT_SUCCESS);
}
