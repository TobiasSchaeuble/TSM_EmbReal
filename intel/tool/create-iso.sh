#------------------------
#create-iso.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#------------------------
#calling from work
genisoimage -R \
            -b stage2_eltorito \
	    -no-emul-boot \
	    -boot-load-size 4 \
	    -boot-info-table \
	-o ../sos.iso ../iso
