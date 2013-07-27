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
    	// �����ļ������
		java.io.FileOutputStream fos;
		try {
			fos = new java.io.FileOutputStream(filePath);
			 
		    fos.write("hahahahahahahahaha".getBytes());
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        //д���ļ���ʶ��Ϣ 
   

        
        
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
//        // ����һ���½��� 
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
     
            // ����BufferedReader 
         //   BufferedReader buf = new BufferedReader(new InputStreamReader(is)); 
//            do { 
//                line = buf.readLine(); 
//                // ǰ���м������� 
//                if (line.startsWith("User")) { 
//                    // ������һ��ʱ�������ٶ�ȡ��һ�� 
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
     * ִ��һ��shell����������ַ���ֵ 
     * 
     * @param cmd 
     * ��������&������ɵ����飨���磺{"/system/bin/cat", "/proc/version"}�� 
     * @param workdirectory 
     * ����ִ��·�������磺"system/bin/"�� 
     * @return ִ�н����ɵ��ַ��� 
     * @throws IOException 
     */ 
    public static synchronized String run(String[] cmd, String workdirectory) 
            throws IOException { 
        StringBuffer result = new StringBuffer(); 
        try { 
            // ��������ϵͳ���̣�Ҳ������Runtime.exec()������ 
            // Runtime runtime = Runtime.getRuntime(); 
            // Process proc = runtime.exec(cmd); 
            // InputStream inputstream = proc.getInputStream(); 
            ProcessBuilder builder = new ProcessBuilder(cmd); 
     
            InputStream in = null; 
            // ����һ��·��������·���˾Ͳ�һ����Ҫ�� 
            if (workdirectory != null) { 
                // ���ù���Ŀ¼��ͬ�ϣ� 
                builder.directory(new File(workdirectory)); 
                // �ϲ���׼����ͱ�׼��� 
                builder.redirectErrorStream(true); 
                // ����һ���½��� 
                Process process = builder.start(); 
     
                // ��ȡ���̱�׼����� 
                in = process.getInputStream(); 
                byte[] re = new byte[1024]; 
                while (in.read(re) != -1) { 
                    result = result.append(new String(re)); 
                } 
            } 
            // �ر������� 
            if (in != null) { 
                in.close(); 
            } 
        } catch (Exception ex) { 
            ex.printStackTrace(); 
        } 
        return result.toString(); 
    }
    
    //ִ��linux�������ע������
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