/**
 * FUNCTON:
 * - strdup()
 * - gnl()
 * 
 * @param
 * static char buffer[BUFFER_SIZE] : Static buffer to hold the content read from the file
 * char line[7000] : Line buffer to hold the current line being read (limited to 70000 chars)
 * static int buffer_read : Static variable to keep track of how many bytes were read into the buffer
 * static int buffer_pos : Static variable to track the current position in the buffer
 * int i;
 * 
 */

#include "get_next_line.h"
//strdup
char *ft_strdup(char *s)
{
	char *dest;
	int i = 0;

	while (s[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//gnl
char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_read;
	static int buffer_pos;
	char line[70000];//reserves a fixed amount of memory (70,000 bytes) 
	int i;
	//char *line : dynamically allocate memory (like with malloc() -> This would require resizing (reallocating) memory 

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)// Start an infinite loop to read characters
	{
		//checks when we’ve processed all characters in the buffer, indicating it’s time to read more data from the file.
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);// Read more data from the file into the buffer
			buffer_pos = 0;// Reset the buffer position
			if (buffer_read <= 0)// If read() returns 0 or negative, break the loop (end of file or error)
				break ;
		}
		if (line[i] == '\n') // Stop reading when encountering a newline character
			break ;
		line[i] = buffer[buffer_pos++];
		i++;	
	}
	line[i] = '\0';
	if (i == 0)//i == 0 -> no charactes copied frm the file
		return (NULL);
	return (ft_strdup(line));
}

int main()
{
    int fd = open("./txt.txt", O_RDONLY);
    printf("%s", get_next_line(fd));
    return (0);
}