package net.example.root.base;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
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

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {



    Button bt;
    TextView tv;
    static int pulso=0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
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

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);



        bt=findViewById(R.id.tvTexto);

        tv=findViewById(R.id.textView2);
        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                pulso++;
                tv.setText("Pulso boton"+pulso);
                Snackbar.make(v, "Pulso boton"+pulso, Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        bt.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                mandar2();
                pulso++;
                Toast.makeText(getApplicationContext(),"Se mantiene pulsado",Toast.LENGTH_SHORT).show();
                return true;
            }
        });
        Button env=findViewById(R.id.enviar);
        env.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(),"Se mantiene pulsado",Toast.LENGTH_SHORT).show();

            }
        });
        Button mandar_dato=findViewById(R.id.enviar);
        mandar_dato.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mandar();
            }
        });



        Button cambiar_de_ventana=findViewById(R.id.recibir_datos);
        cambiar_de_ventana.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent ventana=new Intent(MainActivity.this,ventana_dos.class);
                EditText valor_IP=(EditText)findViewById(R.id.editIP);

                ventana.putExtra("IP",valor_IP.getText().toString());
                startActivity(ventana);
            }
        });
        Button cambiar_a_barra=findViewById(R.id.barra_button);
        cambiar_a_barra.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent ventana=new Intent(MainActivity.this,barra.class);
                EditText valor_IP=(EditText)findViewById(R.id.editIP);

                ventana.putExtra("IP",valor_IP.getText().toString());
                startActivity(ventana);
            }
        });


    }
    public void mandar2()
    {

        Thread nt=new Thread()
        {
            @Override
            public void run() {
                EditText valor_x=(EditText)findViewById(R.id.editx);
                EditText valor_y=(EditText)findViewById(R.id.edity);
                EditText valor_IP=(EditText)findViewById(R.id.editIP);

                try {
                    final String res;
                    httpandler httpand=new httpandler();
                    res=httpand.post(valor_x.getText().toString(),valor_y.getText().toString(),valor_IP.getText().toString());

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(),res,Toast.LENGTH_SHORT).show();
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
    public void mandar()
    {
        Thread nt=new Thread()
        {
            @Override
            public void run() {
                EditText valor_x=(EditText)findViewById(R.id.editx);
                EditText valor_y=(EditText)findViewById(R.id.edity);
                EditText valor_IP=(EditText)findViewById(R.id.editIP);

                try {
                    final String res;
                    res=enviarpost(valor_x.getText().toString(),valor_y.getText().toString(),valor_IP.getText().toString());

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(),res,Toast.LENGTH_SHORT).show();
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
    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_camera) {
            // Handle the camera action
        } else if (id == R.id.nav_gallery) {

        } else if (id == R.id.nav_slideshow) {

        } else if (id == R.id.nav_manage) {

        } else if (id == R.id.nav_share) {

        } else if (id == R.id.nav_send) {

        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }




}
