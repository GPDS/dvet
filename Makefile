RM = rm -fv

all:

	@echo 'Compilando arquivo Image'
	g++ -c src/Image.cpp -o src/Image.o 

	@echo 'Compilando arquivo Video'
	g++ -c src/Video.cpp -o src/Video.o 

	@echo 'Compilando arquivo Sobel'
	g++ -c src/Sobel.cpp -o src/Sobel.o 

	@echo 'Compilando arquivo PSNR'
	g++ -c src/PSNR.cpp -o src/PSNR.o 

	@echo 'Compilando arquivo SSIM'
	g++ -c src/SSIM.cpp -o src/SSIM.o 
	@echo 'Compilando arquivo PWSSIM'
	g++ -c src/PWSSIM.cpp -o src/PWSSIM.o 

	@echo 'Compilando arquivo main'
	g++ -c src/main.cpp -o src/main.o 

	@echo 'Compilando gerando executável'
	g++ src/Image.o src/Video.o src/Sobel.o src/PSNR.o src/SSIM.o src/PWSSIM.o src/main.o -o main

clean:
	@echo 'Cleaning object files'
	$(RM) src/*.o store/*.txt main





