#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

// make shift arena
char 		*file_contents 	= nullptr;
ssize_t 	file_size		= 0;
ssize_t		buffer_size		= 0;

int open_file(const char *file_name){
	int fd = open(file_name, O_RDONLY);
	if(fd <= 0){
		std::cerr << "ERROR OPEN: " << file_name << ' ' << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	return fd;
}

void read_file(int fd){

	file_size = lseek(fd, 0, SEEK_END);
	if(file_size == -1){
		std::cerr << "ERROR SEEK TO END: " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}

	if( lseek(fd, 0, SEEK_SET) == -1){
		std::cerr << "ERROR SEEKING TO START: " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}

	if(file_size > buffer_size){
		delete[] file_contents;
		file_contents = new char[file_size];
		buffer_size = file_size;
	}

	size_t read_result = read(fd, file_contents, file_size);

	if(read_result <= 0){
		std::cerr << "ERROR READ: " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}

}


int main(int argc, const char *argv[]){

	if(argc < 2){
		std::cout << "No input File detected, Provide a Path to a File to use." << std::endl;
		return EXIT_FAILURE;
	}
	for(int i = 1; i < argc; i++){
		int file = open_file(argv[i]);
		read_file(file);
		write(STDOUT_FILENO, file_contents, file_size);
		file_size = 0;
		close(file);
	}
	delete[] file_contents;
	return 0;
}
