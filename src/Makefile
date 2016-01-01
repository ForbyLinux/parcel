cc=g++
args=-O2
output=parcel
includes=-lcurl -lz

make:
	$(cc) $(args) *.cpp -o $(output) $(includes)
	cp $(output) ../

clean:
	rm $(output)
