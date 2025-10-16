# Exercise 4 Solutions 

## Ex1 

1) 
we can type ls -ld /path to see permissions 

r means read permission.
w means write permission.
x means executable permission.
- means the permission is not set.

ls -ld $SCRATCH
drwxr-x---+ 2 iyakushe uzh8 4096 Sep 18 11:22 /capstor/scratch/cscs/iyakushe

taking the directory of random user, 

drwxr-xr-x+ 21 ebaldi em00 4096 Oct  2 11:59 ebaldi

ebaldi has read/write/execute permissions, but group and others have read/execute only

2) 
inside of home I get read/write by default 
-rw-r--r-- 1 iyakushe uzh8      0 Oct 16 14:55 test_f


3) 
drwx------ 2 meberlei uzh8 4096 Oct 15 11:28 /users/meberlei
------ means there are no permission to any other user but meberlei, any action by other user would give simply "/users/meberlei: Permission denied"

4) chmod 700 /directory_name

5) created the file and gave permissions with chmod 

-rw-rw----+ 1 iyakushe uzh8 0 Oct 16 15:31 myfile.txt

6) since I'm the owner but have no permissions I still could use chmod to give me permissions back 

## Ex2 
1) 
    1) grep '00$' binary.txt
    2) grep '^1.*1$' binary.txt
    3) grep '110' binary.txt
    4) grep '\(.*1\)\{3,\}' binary.txt
    5) grep '111' binary.txt

2) the sript and output are in the folder /measured

## Ex3

1) 

20: 2 2 5

31: 31

we seee that 31 is prime hence returns  one number 

2) scipt is in the main folder , usage: 
./isprime.sh 31
31 is prime

3) 
iyakushe@eiger-ln004:~/hpc_esc_401_solutions/exercise_session_04> ./isprime.sh 4230283
4230283 is prime
iyakushe@eiger-ln004:~/hpc_esc_401_solutions/exercise_session_04> ./isprime.sh 4572862171001
4572862171001 is prime