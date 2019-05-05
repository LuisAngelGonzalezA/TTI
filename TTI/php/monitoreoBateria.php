<?php

include("conexion.php");
$nombre=$_GET["nombre"];

	$sql = "SELECT * FROM sensadoB 
WHERE (hora >= '2019-04-30'  and hora>='2019-04-30') and id_bateria = (SELECT id_bateria FROM bateria WHERE nombre LIKE '{$nombre}')
GROUP BY ((60/15) * HOUR((hora)) + FLOOR(MINUTE(hora)/15))";


	$json = array();
	$resultado = mysqli_query($conn,$sql);

	$operacion["operacion"] = '5';
	$json['datos'][] = $operacion;

	if($sql){
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		mysqli_close($conn);
		echo json_encode($json);
	}

?>
