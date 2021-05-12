snd-hda-codec-realtek-objs :=	patch_realtek.o
obj-m += snd-hda-codec-realtek.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

install:
	rm /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko || true
	cp snd-hda-codec-realtek.ko /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko

backup:
	cp /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko.bak

restore:
	rm /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko || true
	cp /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko.bak /usr/lib/modules/$(shell uname -r)/kernel/sound/pci/hda/snd-hda-codec-realtek.ko

dkms-install:
	mkdir /usr/src/omen-sound-0.1
	cp * /usr/src/omen-sound-0.1/
	dkms build -m omen-sound -v 0.1
	dkms install -m omen-sound -v 0.1
