#!/bin/bash

NC='\033[0m' # No Color

BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
On_IPurple='\033[0;105m'  # Purple



#echo 10 sized arrays 
#time a.out 10 q
#echo -e "${BIBlue}end of test 1${NC} - of size 10" 
#time a.out 10 i
#echo -e "${BIBlue}end of test 2${NC} - of size 10"
#time a.out 10 b
#echo -e "${BIBlue}end of test 3${NC} - of size 10"
#time a.out 10 s
#echo -e "${BIBlue}end of test 4${NC} - of size 10\n"


#echo 1000 sized arrays
#time a.out 1000 q
#echo -e "${BIYellow}end of test 1${NC} - of size 1000" 
#time a.out 1000 i
#echo -e "${BIYellow}end of test 2${NC} - of size 1000" 
#time a.out 1000 b
#echo -e "${BIYellow}end of test 3${NC} - of size 1000" 
#time a.out 1000 s
#echo -e "${BIYellow}end of test 4${NC} - of size 1000\n" 



echo 100000 sized arrays
time a.out 100000 q
echo -e "${On_IPurple}end of test 1${NC} - of size 100000" 
time a.out 100000 i
echo -e "${On_IPurple}end of test 2${NC} - of size 100000" 
time a.out 100000 b
echo -e "${On_IPurple}end of test 3${NC} - of size 100000" 
time a.out 100000 s
echo -e "${On_IPurple}end of test 4${NC} - of size 100000\n" 







#echo 10000000 sized arrays
#time a.out 10000000 Q
#echo -e "${BIGreen}end of test 1${NC} - of size 10"
#time a.out 10000000 B
#echo -e "${BIGreen}end of test 1${NC} - of size 10"
#time a.out 10000000 I
#echo -e "${BIGreen}end of test 1${NC} - of size 10"
#time a.out 10000000 S
#echo -e "${BIGreen}end of test 1${NC} - of size 10"


