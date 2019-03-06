package net.example.root.base;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.HttpContext;

import java.util.ArrayList;
import java.util.List;

public class barra extends AppCompatActivity {
    String IP=null;
    String x="0",y="0";
    int valoresx=90,valoresy=90;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_barra);
        IP=recibirDatos();
        final TextView valorx,valory;
        valorx=findViewById(R.id.porcentajex);
        valory=findViewById(R.id.porcentajey);
        SeekBar see2=findViewById(R.id.seekBar2);
        SeekBar see3=findViewById(R.id.seekBar3);


        see2.setProgress(valoresx);
        valorx.setText(valoresx+" % ");
        see3.setProgress(90);
        valory.setText(valoresy+" % ");
        see2.setMax(180);
        see3.setMax(180);
        see2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                valorx.setText(String.valueOf((progress)+" % "));
                x=String.valueOf(progress);
                mandar(x,y);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        see3.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                valory.setText(String.valueOf((progress)+" % "));
                y=String.valueOf(progress);
                mandar(x,y);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });





    }

    public String recibirDatos()
    {
        Bundle extras = getIntent().getExtras();
        return extras.getString("IP");
    }
    public void mandar(final String valor_x,final String valor_y)
    {
        Thread nt=new Thread()
        {
            @Override
            public void run() {
                //EditText valor_x=(EditText)findViewById(R.id.editx);
                //EditText valor_y=(EditText)findViewById(R.id.edity);
                EditText valor_IP=(EditText)findViewById(R.id.editIP);

                try {
                    final String res;
                    res=enviarpost(valor_x,valor_y,IP);

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            //Toast.makeText(getApplicationContext(),res,Toast.LENGTH_SHORT).show();
                        }
                    });

                }
                catch (Exception e)
                {

                }
            }
        };
        nt.start();
    }
    public String enviarpost(String x,String y,String IP)
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
