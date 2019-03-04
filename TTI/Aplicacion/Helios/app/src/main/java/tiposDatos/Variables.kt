package tiposDatos


import android.util.Log


class Variables{

    private var variable = 1
    private var variable2: Byte = 1.toByte()


    private var variable3 = -123



    private fun showCaseByte(){
        Log.w("Variable","Es Integer " + (variable is Int))
        Log.w("variable 2","Es un Byte" + (variable2 is Byte))
    }


    private fun showCaseInt(){
        Log.w("variable2","")
        variable3 = Int.MAX_VALUE

    }

    public fun showCases(){
        showCaseByte()
        showCaseInt()
    }

}