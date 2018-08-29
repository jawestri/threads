#/bin/bash

#Script for Case Study by: Jamie Westrick
#script to analyze data from sensordata2.txt which contains-
#random temp values from multiple threads. The results are shown in a- 
#pop-up dialog box using zenity


#sort value low to high and store in new file
sort -k 3,3 sensordata2.txt > output.txt

#cut tempurature values into ordered array
array=($(cut -d' ' -f3 output.txt))

printf "List of Temperatures sorted: \n"
#print out temperatures
for array in "${array[@]}";
        do
            echo $array
        done

n=20
m=$n
sum=0

#calc average temp 
while [ $n -gt 0 ]
do
  
    num=${array[`expr $n - 1`]}    
    sum=`expr $sum + $num`
    n=`expr $n - 1`
done
  
avg=`echo "scale=2; $sum / $m" | bc -l`

#calc min and max temp
min=`echo $(cut -d" " -f3 output.txt | sort -n | head -1)`
max=`echo $(cut -d" " -f3 output.txt | sort -n | tail -1)`

#output results with zenity
zenity --info --title="Temperature Analysis " --text="Average Temp: $avg °F\n Max Temp: $max °F \nMin Temp: $min °F"






