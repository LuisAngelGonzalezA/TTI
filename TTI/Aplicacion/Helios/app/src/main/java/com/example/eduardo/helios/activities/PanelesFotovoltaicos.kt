package com.example.eduardo.helios.activities


import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.view.animation.AnimationUtils
import android.widget.FrameLayout
import android.widget.ImageSwitcher
import android.widget.ImageView
import com.example.eduardo.helios.R
import com.squareup.picasso.Picasso
import kotlinx.android.synthetic.main.activity_paneles_fotovoltaicos.*
import java.io.BufferedReader
import java.io.InputStream
import com.example.eduardo.helios.utileria.ImageModel
import java.util.*



class PanelesFotovoltaicos : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_paneles_fotovoltaicos)

        funcionamientoTV.text = leerArchivo().first()
        instalacionTV.text = leerArchivo().last()

        cargarImagenes()



    }

    /**
     * Metodo que permite leer el archivo Funcionamiento almacenado en el la carpeta raw
     */
    private fun leerArchivo():List<String>{
        val ins: InputStream = resources.openRawResource(R.raw.fucionamiento)
        val br: BufferedReader = ins.bufferedReader()
        return br.readLines()
    }

    /**
     * Metodo que permite Cargar las imagenes de este activity
     */
    private fun cargarImagenes() {

        Picasso.with(this).load("https://www.monsolar.com/blog/wp-content/uploads/2014/02/panel-solar-fotovoltaico.jpg")
                .fit()
                .centerInside()
                .into(instalacionIV)

        Picasso.with(this).load("http://www.sunplicity.cl/wp-content/uploads/2016/11/paneles-solares-1170x780.jpg")
                .fit()
                .centerInside()
                .into(funcionamientoIV)


    }





}
