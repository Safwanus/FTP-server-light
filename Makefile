all : cftp.c sftp.c
	gcc cftp.c -o ftpcli
	gcc sftp.c -o ftpserv
clean :
	rm -rf ft*
