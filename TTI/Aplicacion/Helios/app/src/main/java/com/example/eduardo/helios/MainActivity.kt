package com.example.eduardo.helios

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.constraint.ConstraintLayout
import android.support.design.widget.Snackbar
import android.widget.Button
import android.widget.Toast
import com.example.eduardo.helios.activities.MonitorearMecanismo
import com.example.eduardo.helios.activities.Noticias
import com.example.eduardo.helios.activities.OrientacionOptima
import com.example.eduardo.helios.activities.PanelesFotovoltaicos


class  MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)


        setContentView(R.layout.activity_main)

        val btnNoticias = findViewById<Button>(R.id.btnNoticias)
        val btnPaneles = findViewById<Button>(R.id.btnPaneles)
        val btnOrientacion = findViewById<Button>(R.id.btnOrientacion)
       // val btnMonitorear = findViewById<Button>(R.id.btnMonitorear)

        /*fun example(){
           val intent = Intent(this,CicloVida::class.java)
           startActivity(intent)
       }*/


        fun irNoticias() = startActivity(Intent(this, Noticias::class.java))
        fun irPaneles() = startActivity(Intent(this, PanelesFotovoltaicos::class.java))
        fun irOrientacion() = startActivity(Intent(this, OrientacionOptima::class.java))




        fun showToast(){
            Toast.makeText(this," PROBANDO ", Toast.LENGTH_LONG).show()
        }

        fun showSnackBar(){
            val layout = findViewById<ConstraintLayout>(R.id.constraint)
            Snackbar.make(layout,"Este es un SNACKBAR", Snackbar.LENGTH_LONG).setAction("Devolver"){
                Snackbar.make(layout,"Deshecho", Snackbar.LENGTH_LONG).show()
            }.show()
        }

        btnNoticias.setOnClickListener { irNoticias() }
        btnPaneles.setOnClickListener { irPaneles() }
        btnOrientacion.setOnClickListener { irOrientacion() }










    }
}
