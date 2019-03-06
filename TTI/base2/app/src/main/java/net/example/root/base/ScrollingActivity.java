package net.example.root.base;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.HttpContext;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;

import java.util.ArrayList;
import java.util.List;

public class ScrollingActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scrolling);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        /*final String IP="192.168.100.15";

           Thread tr=new Thread()
            {
                @Override
                public void run() {
                    final String Resultado=leer(IP);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            cargarListado(ObtDatosJson(Resultado));
                        }
                    });
                }
            };
            */



    }

    public String recibirDatos()
    {
        Bundle extras = getIntent().getExtras();
        return extras.getString("IP");

    }

    public ArrayList<String> ObtDatosJson(String response)
    {
        ArrayList<String> listado=new ArrayList<String>();
        try
        {
            JSONArray json=new JSONArray(response);
            String texto="";
            for (int i=0;i<json.length();i++)
            {
                texto=json.getJSONObject(i).getString("x")+"    -     "+json.getJSONObject(i).getString("y");
                listado.add(texto);
            }

        }catch (Exception e)
        {

        }
        return listado;
    }


    public String leer(String IP)
    {
        String mensaje="";
        HttpClient httpClient=new DefaultHttpClient();
        HttpContext httpContext=new BasicHttpContext();
        HttpGet httpGet=new HttpGet("http://"+IP+"/android_select.php");
        try {
            HttpResponse response=httpClient.execute(httpGet,httpContext);
            HttpEntity httpEntity=response.getEntity();
            mensaje=EntityUtils.toString(httpEntity,"UTF-8");
        } catch (Exception e) {
            mensaje="Error no se manda nada";
        }


        return mensaje;
    }

    public void cargarListado(ArrayList<String> datos)
    {
        ArrayAdapter<String> arrayAdapter=new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,datos);
        ListView lista=(ListView)findViewById(R.id.listviewer1);
        lista.setAdapter(arrayAdapter);
    }
}
