package net.example.root.base;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.HttpContext;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;

import java.util.ArrayList;

public class ventana_dos extends AppCompatActivity {

    String IP=null;
    ListView lista=null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ventana_dos);

        IP=recibirDatos();
        lista=findViewById(R.id.lista_de_servo);
        /*
        String[] values=new String[]{
          "ironman","capitan America","hulk","Thor"
        };
        ArrayAdapter<String> adapter=new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,values);
        list.setAdapter(adapter);
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                int iten=position;
                String itemval=(String)list.getItemAtPosition(position);
                Toast.makeText(getApplicationContext(),"Posicion : "+iten+"-- Valor: "+itemval,Toast.LENGTH_LONG).show();
            }
        });
    */
        obtener_Datos();

    }

    public String recibirDatos()
    {
        Bundle extras = getIntent().getExtras();
        return extras.getString("IP");
    }


    public void obtener_Datos()
    {
        Thread tr=new Thread()
        {
            @Override
            public void run() {
                final String Resultado;
                Resultado = leer(IP);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getApplicationContext(),"EL valor es : "+Resultado,Toast.LENGTH_SHORT).show();
                        cargarListado(ObtDatosJson(Resultado));
                    }
                });
            }
        };
        tr.start();
    }


    public ArrayList<String> ObtDatosJson(String response)
    {
        ArrayList<String> listado=new ArrayList<String>();
        try
        {
            JSONArray json=new JSONArray(response);
            String texto="";
            for (int i=0;i<json.length();i++) {
                texto = "Servo en x :"+json.getJSONObject(i).getString("posicion_x") + "    -     "
                        +"Servo en y :"+json.getJSONObject(i).getInt("posicion_y");
                listado.add(texto);
            }

        }catch (Exception e)
        {
            listado.add("Error en los datos");
        }
        return listado;
    }


    public String leer(String IP)
    {
        String mensaje=null;
        HttpClient httpClient=new DefaultHttpClient();
        HttpContext httpContext=new BasicHttpContext();
        HttpGet httpGet=new HttpGet("http://"+IP+"/android_select.php");
        try {
            HttpResponse response=httpClient.execute(httpGet,httpContext);
            HttpEntity httpEntity=response.getEntity();
            mensaje=EntityUtils.toString(httpEntity,"UTF-8");
            //mensaje="Si llegan los datos";
        } catch (Exception e) {
            mensaje="Error no se manda nada";
        }


        return mensaje;
    }

    public void cargarListado(ArrayList<String> datos)
    {
        ArrayAdapter<String> arrayAdapter=new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,datos);
        //ListView lista=(ListView)findViewById(R.id.lista_de_servo);
        lista.setAdapter(arrayAdapter);
        lista.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                int iten=position;
                String itemval=(String)lista.getItemAtPosition(position);
                Toast.makeText(getApplicationContext(),"Posicion : "+iten+"-- Valor: "+itemval,Toast.LENGTH_LONG).show();
            }
        });
    }


}
