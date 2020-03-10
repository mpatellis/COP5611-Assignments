import java.io.IOException;
import java.util.StringTokenizer;
import java.util.HashMap;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Problem3 
{

    public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable>
    {
        private final static IntWritable one = new IntWritable(1);
        private Text word = new Text();

        public void map(Object key, Text value, Context context) throws IOException, InterruptedException 
        {
            String pre_line = value.toString();
            String post_line = "";
            int pre_len = pre_line.length();

            for (int i = 0; i < pre_len; i++)
            {
                char c = pre_line.charAt(i);

                if (!Character.isLetter(c) && c != ' ')
                  continue;
                post_line = post_line + Character.toLowerCase(c);
            }

            HashMap<String, Integer> seen = new HashMap<>();
            String[] words = post_line.split("\\s+");
            int len = words.length;

            for (int i = 0; i < len; i++)
            {
                String first = words[i];

                if (seen.get(first) == null)
                {
                    seen.put(first, 1);

                    for (int j = 0; j < len; j++)
                    {
                        if (i == j)
                            continue;

                        String res = first + "," + words[j];
                        word.set(res);
                        context.write(word, one);
                    }
                }
            }
        }
    }

    public static class IntSumReducer extends Reducer<Text,IntWritable,Text,IntWritable> 
    {
        private IntWritable result = new IntWritable();

        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException 
        {
            int sum = 0;
            for (IntWritable val : values) 
            {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception 
    {
        Configuration conf = new Configuration();

        Job job = Job.getInstance(conf, "Problem 3");
        job.setJarByClass(Problem3.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(IntSumReducer.class);
        job.setReducerClass(IntSumReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);

        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
