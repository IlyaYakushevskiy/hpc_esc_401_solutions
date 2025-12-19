## HW 13 

### Ex1 

I've created image from snapshot "hadoop" and ssh-ed the VM succesfully. Accessed the hadoop interface w/ http://localhost:9870/dfshealth.html#tab-overview and http://localhost:8088/cluster , then I ran start-yarn.sh and start-dfs.sh

### Ex2 


1)hadoop splited data into 7 chunks, so it launched 7 parallel mapper instances to process them
2) 



Output : 
```python
2025-12-19 12:21:06,152 INFO mapreduce.Job: Counters: 55
        File System Counters
                FILE: Number of bytes read=5550040
                FILE: Number of bytes written=13348333
                FILE: Number of read operations=0
                FILE: Number of large read operations=0
                FILE: Number of write operations=0
                HDFS: Number of bytes read=12914644
                HDFS: Number of bytes written=642476
                HDFS: Number of read operations=26
                HDFS: Number of large read operations=0
                HDFS: Number of write operations=2
                HDFS: Number of bytes read erasure-coded=0
        Job Counters 
                Killed map tasks=1
                Launched map tasks=7
                Launched reduce tasks=1
                Rack-local map tasks=7
                Total time spent by all maps in occupied slots (ms)=81374
                Total time spent by all reduces in occupied slots (ms)=9872
                Total time spent by all map tasks (ms)=81374
                Total time spent by all reduce tasks (ms)=9872
                Total vcore-milliseconds taken by all map tasks=81374
                Total vcore-milliseconds taken by all reduce tasks=9872
                Total megabyte-milliseconds taken by all map tasks=83326976
                Total megabyte-milliseconds taken by all reduce tasks=10108928
        Map-Reduce Framework
                Map input records=35371
                Map output records=538568
                Map output bytes=4472896
                Map output materialized bytes=5550076
                Input split bytes=819
                Combine input records=0
                Combine output records=0
                Reduce input groups=47090
                Reduce shuffle bytes=5550076
                Reduce input records=538568
                Reduce output records=47090
                Spilled Records=1077136
                Shuffled Maps =7
                Failed Shuffles=0
                Merged Map outputs=7
                GC time elapsed (ms)=557
                CPU time spent (ms)=8890
                Physical memory (bytes) snapshot=2086514688
                Virtual memory (bytes) snapshot=21898842112
                Total committed heap usage (bytes)=1804599296
                Peak Map Physical memory (bytes)=301006848
                Peak Map Virtual memory (bytes)=2741604352
                Peak Reduce Physical memory (bytes)=216031232
                Peak Reduce Virtual memory (bytes)=2742444032
        Shuffle Errors
                BAD_ID=0
                CONNECTION=0
                IO_ERROR=0
                WRONG_LENGTH=0
                WRONG_MAP=0
                WRONG_REDUCE=0
        File Input Format Counters 
                Bytes Read=12913825
        File Output Format Counters 
                Bytes Written=642476
```

P.S. If I don't end up submitting it on time, I might be 5-10 min late and upload all the solution to my github, please check the final version on https://github.com/IlyaYakushevskiy/hpc_esc_401_solutions . 

Thank you for the course and have a nice hollidays! :D 


```python

                               |
                             \ ' /
                           -- (*) --
                              >*<
                             >0<@<
                            >>>@<<*
                           >@>*<0<<<
                          >*>>@<<<@<<
                         >@>>0<<<*<<@<
                        >*>>0<<@<<<@<<<
                       >@>>*<<@<>*<<0<*<
         \*/          >0>>*<<@<>0><<*<@<<
     ___\\U//___     >*>>@><0<<*>>@><*<0<<
     |\\ | | \\|    >@>>0<*<0>>@<<0<<<*<@<<
     | \\| | _(UU)_ >((*))_>0><*<0><@<<<0<*<
     |\ \| || / //||.*.*.*.|>>@<<*<<@>><0<<<
jgs  |\\_|_|&&_// ||*.*.*.*|_\\db//_
     """"|'.'.'.|~~|.*.*.*|     ____|_
         |'.'.'.|   ^^^^^^|____|>>>>>>|
         ~~~~~~~~         '""""`------'
------------------------------------------------
```