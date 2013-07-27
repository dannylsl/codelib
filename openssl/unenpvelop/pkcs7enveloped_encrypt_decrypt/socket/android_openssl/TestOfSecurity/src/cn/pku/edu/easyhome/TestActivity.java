package cn.pku.edu.easyhome;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

public class TestActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main); 
        String filePath="/data/data/cn.pku.edu.easyhome/openssl/data";
    	// 创建文件输出流
		java.io.FileOutputStream fos;
		try {
			fos = new java.io.FileOutputStream(filePath);
			 
		    fos.write("hahahahahahahahaha".getBytes());
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        //写放文件标识信息 
   

        
        
        Process p = null;
        try {
            p = Runtime.getRuntime().exec("/data/data/cn.pku.edu.easyhome/openssl/a_signEnvelop\n");
            DataOutputStream pOut = new DataOutputStream(p.getOutputStream());
//            pOut.writeBytes();
//            pOut.flush();
            pOut.writeBytes("exit\n");
            pOut.flush();
            try {
                p.waitFor();
            } catch (InterruptedException e) {
            	Toast.makeText(this, "not root", 1).show();
            }
            if (p.exitValue() == 0)
            	Toast.makeText(this, "root acees", 1).show();
            else
            	Toast.makeText(this, "not rootsssssssssssssssssss"+p.exitValue(), 1).show();
        } catch (IOException e) {
        	Toast.makeText(this, "root acc", 1).show();
        }
        
    }
    public void onCreate222(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
       //  execRootCmdSilent("/data/local/openssl/a_signEnvelop /data/local/openssl/data.txt");
       
    //   String[] str=  {"/data/app/openssl/a_signEnvelop","/data/app/openssl/data.txt"};
       String str2="/data/local/openssl/a_signEnvelop";
       String[] str=  {"/data/local/openssl/a_signEnvelop","/data/local/openssl/data"};
       
       try {
    	   Runtime runtime = Runtime.getRuntime(); 
           Process proc = runtime.exec(str2);
           
 
           InputStream inputstream = proc.getInputStream(); 
           StringBuffer result = new StringBuffer(); 
           
           byte[] re = new byte[1024]; 
           while (inputstream.read(re) != -1) { 
               result = result.append(new String(re)); 
           } 
           
           proc.waitFor();             
           System.out.println(result);
    	   
    	   
    	 //  execRootCmdSilent(str2);
    	   Process localProcess = Runtime.getRuntime().exec("su");
           Object localObject = localProcess.getOutputStream();
           DataOutputStream localDataOutputStream = new DataOutputStream((OutputStream)localObject);
           localDataOutputStream.writeBytes("/data/local/openssl/a_signEnvelop /data/local/openssl/data\n");
           localDataOutputStream.flush();
           
	   } catch (Exception e) {
		// TODO Auto-generated catch block
		  e.printStackTrace();
	   } 
 
//       try {
//		   run(str);
//	    } catch (Exception e) {
//		// TODO Auto-generated catch block
//		  e.printStackTrace();
//	    }
          
//        
//        ProcessBuilder builder = new ProcessBuilder("/data/local/a_signEnvelop data.txt"); 
//        
//        // 启动一个新进程 
//        try {
//			Process process = builder.start();
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} 
    }
    
    public static synchronized String run(String[] cmd) { 
        String line = ""; 
        InputStream is = null; 
        try { 
            Runtime runtime = Runtime.getRuntime(); 
            Process proc = runtime.exec(cmd); 
         //   is = proc.getInputStream(); 
     
            // 换成BufferedReader 
         //   BufferedReader buf = new BufferedReader(new InputStreamReader(is)); 
//            do { 
//                line = buf.readLine(); 
//                // 前面有几个空行 
//                if (line.startsWith("User")) { 
//                    // 读到第一行时，我们再读取下一行 
//                    line = buf.readLine(); 
//                    break; 
//                } 
//            } while (true); 
     
//            if (is != null) { 
//                buf.close(); 
//                is.close(); 
//            } 
        } catch (IOException e) { 
            e.printStackTrace(); 
        } 
        return line; 
    }
    /** 
     * 执行一个shell命令，并返回字符串值 
     * 
     * @param cmd 
     * 命令名称&参数组成的数组（例如：{"/system/bin/cat", "/proc/version"}） 
     * @param workdirectory 
     * 命令执行路径（例如："system/bin/"） 
     * @return 执行结果组成的字符串 
     * @throws IOException 
     */ 
    public static synchronized String run(String[] cmd, String workdirectory) 
            throws IOException { 
        StringBuffer result = new StringBuffer(); 
        try { 
            // 创建操作系统进程（也可以由Runtime.exec()启动） 
            // Runtime runtime = Runtime.getRuntime(); 
            // Process proc = runtime.exec(cmd); 
            // InputStream inputstream = proc.getInputStream(); 
            ProcessBuilder builder = new ProcessBuilder(cmd); 
     
            InputStream in = null; 
            // 设置一个路径（绝对路径了就不一定需要） 
            if (workdirectory != null) { 
                // 设置工作目录（同上） 
                builder.directory(new File(workdirectory)); 
                // 合并标准错误和标准输出 
                builder.redirectErrorStream(true); 
                // 启动一个新进程 
                Process process = builder.start(); 
     
                // 读取进程标准输出流 
                in = process.getInputStream(); 
                byte[] re = new byte[1024]; 
                while (in.read(re) != -1) { 
                    result = result.append(new String(re)); 
                } 
            } 
            // 关闭输入流 
            if (in != null) { 
                in.close(); 
            } 
        } catch (Exception ex) { 
            ex.printStackTrace(); 
        } 
        return result.toString(); 
    }
    
    //执行linux命令但不关注结果输出
    protected static void execRootCmdSilent(String paramString)
    {
      try
      {
        Process localProcess = Runtime.getRuntime().exec("su");
        Object localObject = localProcess.getOutputStream();
        DataOutputStream localDataOutputStream = new DataOutputStream((OutputStream)localObject);
        String str = String.valueOf(paramString);
        localObject = str + "\n";
        localDataOutputStream.writeBytes((String)localObject);
        localDataOutputStream.flush();
        localDataOutputStream.writeBytes("exit\n");
        localDataOutputStream.flush();
        localProcess.waitFor();
        localObject = localProcess.exitValue();
        return;
      }
      catch (Exception localException)
      {
        localException.printStackTrace();
      }
    }
}