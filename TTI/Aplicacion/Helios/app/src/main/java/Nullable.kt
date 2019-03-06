
class Nullable{


    private lateinit var variable: String
    private var variable2: String? = null



    private fun showCaseExplicito(){
        throw NullPointerException()
    }

    private fun caseOperadorAdmiracion(var1: String?){
        var1.toString()
        var1!!.toString()
    }


    private fun inconsistencia(){
        variable.length
        variable2?.length
    }

     public fun showCases(){
        showCaseExplicito()
        caseOperadorAdmiracion("Hold")
        inconsistencia()
    }
}