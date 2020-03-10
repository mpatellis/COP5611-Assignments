The program was tested and ran on a standalone version of Apache Hadoop 2.9.2 using Java 8

To compile the following two commands were used:
$ $HADOOP_HOME/bin/hadoop com.sun.tools.javac.Main Problem3.java
$ jar cf p3.jar Problem3*.class

To run the program the following command was used:
$ $HADOOP_HOME/bin/hadoop jar p3.jar Problem3 <HDFS path to input> <HDFS path to output>