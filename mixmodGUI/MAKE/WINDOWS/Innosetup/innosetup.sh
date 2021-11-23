#!/bin/bash

#usage : lancer './innosetup.sh nom-repertoire' dans le repertoire parent de celui que l'on veut mettre dans l'installeur
#ex : Si le répertoire TMP contient le répertoire mixmodForMatlab (dont onveut un installeur), dans le répertoire TMP, il faut la ncer : './innosetup.sh mixmodForMatlab'




function ecritrep {
	echo Name:\ \"{app}\\$1\"\;\ Flags:\ uninsalwaysuninstall
}

function ecritfic {
	tmp=$1
	echo Source:\ \"$tmp\\*.*\"\;\ DestDir:\ \"{app}\\$tmp\"\;\ Flags:\ ignoreversion
}



#test le nombre d'argument passé
if  test $# -ne 1
then
        echo 'il manque un argument : le répertoire du logiciel à installer'
else

echo
echo [Dirs]
cd $1
for fic1 in `ls -A`
do
	if test -d $fic1 
	then
		
		courant1=$fic1
		ecritrep $courant1
		cd $fic1
		for fic2 in `ls -A`
		do
			if test -d $fic2 
			then
				courant2=$courant1\\$fic2
				ecritrep $courant2
				cd $fic2
				for fic3 in `ls -A`
				do
					if test -d $fic3 
					then
						courant3=$courant2\\$fic3
						ecritrep $courant3
						cd $fic3
						for fic4 in `ls -A`
						do
							if test -d $fic4 
							then
								courant4=$courant3\\$fic4
								ecritrep $courant4
								cd $fic4
								for fic5 in `ls -A`
								do
									if test -d $fic5 
									then
										courant5=$courant4\\$fic5
										ecritrep $courant5
										cd $fic5
										for fic6 in `ls -A`
										do
											if test -d $fic6 
											then
												courant6=$courant5\\$fic6
												ecritrep $courant6
											fi	
										done
										cd ..
									fi
								done
								cd ..
							fi
						done
						cd ..
					fi
				done
				cd ..
			fi
		done
		cd ..
	fi
done
cd ..




echo
echo \[Files\]
echo Source:\ \"*.*\"\;\ DestDir\ :\ \"{app}\"\;\ Flags:\ ignoreversion
cd $1
for fic1 in `ls -A`
do
	if test -d $fic1 
	then
		
		courant1=$fic1
		ecritfic $courant1
		cd $fic1
		for fic2 in `ls -A`
		do
			if test -d $fic2 
			then
				courant2=$courant1\\$fic2
				ecritfic $courant2
				cd $fic2
				for fic3 in `ls -A`
				do
					if test -d $fic3 
					then
						courant3=$courant2\\$fic3
						ecritfic $courant3
						cd $fic3
						for fic4 in `ls -A`
						do
							if test -d $fic4 
							then
								courant4=$courant3\\$fic4
								ecritfic $courant4
								cd $fic4
								for fic5 in `ls -A`
								do
									if test -d $fic5 
									then
										courant5=$courant4\\$fic5
										ecritfic $courant5
										cd $fic5
										for fic6 in `ls -A`
										do
											if test -d $fic6 
											then
												courant6=$courant5\\$fic6
												ecritfic $courant6
											fi	
										done
										cd ..
									fi
								done
								cd ..
							fi
						done
						cd ..
					fi
				done
				cd ..
			fi
		done
		cd ..
	fi
done
cd ..

fi