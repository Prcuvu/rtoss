gcc -Os -momit-leaf-frame-pointer -I. -DNONDLL=1 repng2jpeg.c libbgd-static.a -lstdc++ -lgdi32 -Wl,-Bstatic -lpng -lz -ljpeg -Wl,-Bdynamic -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -s -o repng2jpeg  
