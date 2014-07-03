
#For 32 bit systems
#OUTPUT_ARCHITECTURE=elf32-i386
#BINARY_ARCHITECTURE=i386


OUTPUT_ARCHITECTURE=elf64-x86-64
BINARY_ARCHITECTURE=i386


cd game_resorces/strings
FILES=$(ls -1 *[^o~] | sed 's#^.*/##g')

for f in $FILES
do
    echo "Processing '$f'"
    echo "objcopy --input binary --output $OUTPUT_ARCHITECTURE --binary-architecture $BINARY_ARCHITECTURE ./game_resorces/strings/$f ./bin/res/strings/$f.o"
    objcopy --input binary --output $OUTPUT_ARCHITECTURE --binary-architecture $BINARY_ARCHITECTURE $f ../../bin/res/strings/$f.o
done

#objcopy --input binary --output $(OUTPUT_ARCHITECTURE) --binary-architecture $(BINARY_ARCHITECTURE) * *.o
