import android.util.Log


class Operadores{

    private fun equality(){
        var a = 5
        var b = 5

        Log.w("REFERENTIAL", "a === b  ${a ===b}")
        Log.w("STRUCTURAL", "a == b ${a == b}")
    }


    private fun case2(){
        val p1 = PersonNomal()
        val p2 = PersonNomal()

        Log.w("REFERENTIAL", "a === b  ${p1 ===p2}")
        Log.w("STRUCTURAL", "a == b ${p1 == p2}")
    }


    fun mostrar(){
        equality()
        case2()
    }
}


class PersonNomal{val nombre = "Carlos"}