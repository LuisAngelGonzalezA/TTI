package net.example.root.base;


import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.HttpContext;
import org.apache.http.util.EntityUtils;


import java.util.*;
public class httpandler {


    public String post(String x,String y,String IP)
    {
        String mensaje="";
        HttpClient httpClient=new DefaultHttpClient();
        HttpContext httpContext=new BasicHttpContext();
        HttpPost httpPost=new HttpPost("http://"+IP+"/android_insert.php");
        HttpResponse httpResponse=null;
        try {
            List<NameValuePair> params=new ArrayList<NameValuePair>();
            params.add(new BasicNameValuePair("x",x));
            params.add(new BasicNameValuePair("y",y));
            httpPost.setEntity(new UrlEncodedFormEntity(params));
            httpResponse=httpClient.execute(httpPost,httpContext);
            mensaje=(String)httpResponse.toString();
        } catch (Exception e) {
            mensaje="Error no se manda nada";
        }


        return mensaje;

    }


}
