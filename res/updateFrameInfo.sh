#!/bin/bash
for frame in 120 193 196 241
do
	for ((card=1; card <= 14 ; card++))
	do
		name=$(snmpget -Ov -c public -v 1 192.168.15.$frame .1.3.6.1.4.1.290.9.3.3.21.1.1.1370.1.1.0.$card.$card | sed 's/STRING: "//; s/""/N\/A/; s/"//' )
		case $name in
		XD ) type=3;;
		MDX1 ) type=4;;
		MDX2 ) type=5;;
		NET1 ) type=6;;
		DEC1 ) type=7;;
		DEC2 ) type=8;;
		ENC1 ) type=9;;
		ENC2 ) type=10;;
		N/A ) type=11;;
		DEM1 ) type=18;;
		* ) type=11;;
		esac
		case $frame in
		120 )
			case $card in
			1 ) id=4;;
			2 ) id=5;;
                        3 ) id=6;;
                        4 ) id=7;;
                        5 ) id=8;;
                        6 ) id=9;;
                        7 ) id=10;;
                        8 ) id=11;;
                        9 ) id=12;;
                        10 ) id=13;;
                        11 ) id=14;;
                        12 ) id=15;;
                        13 ) id=16;;
                        14 ) id=48;;
			esac;;
		193 ) 
                        case $card in 
                        1 ) id=19;;
                        2 ) id=20;;
                        3 ) id=21;;
                        4 ) id=22;;
                        5 ) id=23;;
                        6 ) id=24;;
                        7 ) id=25;;
                        8 ) id=26;;
                        9 ) id=27;;
                        10 ) id=28;;
                        11 ) id=29;;
                        12 ) id=30;;
                        13 ) id=31;;
                        14 ) id=32;;
                        esac;;
		196 ) 
                        case $card in 
                        1 ) id=33;;
                        2 ) id=34;;
                        3 ) id=35;;
                        4 ) id=36;;
                        5 ) id=37;;
                        6 ) id=38;;
                        7 ) id=39;;
                        8 ) id=40;;
                        9 ) id=41;;
                        10 ) id=42;;
                        11 ) id=43;;
                        12 ) id=44;;
                        13 ) id=45;;
                        14 ) id=46;;
                        esac;;

		241 ) 
                        case $card in 
                        1 ) id=63;;
                        2 ) id=64;;
                        3 ) id=65;;
                        4 ) id=66;;
                        5 ) id=67;;
                        6 ) id=68;;
                        7 ) id=69;;
                        8 ) id=70;;
                        9 ) id=72;;
                        10 ) id=73;;
                        11 ) id=74;;
                        12 ) id=75;;
                        13 ) id=76;;
                        14 ) id=81;;
                        esac;;

		esac
		echo "change_res $id type_id $type" >> /tmp/command.txt
	done
done
echo "exit" >> ~/command.txt
cd /opt/labrest/
./labrest_client admin admin < /tmp/command.txt >/dev/null 2>&1
rm -rf /tmp/command.txt
exit 0

