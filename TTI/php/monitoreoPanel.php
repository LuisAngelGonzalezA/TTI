<?php

include("conexion.php");
$nombre=$_GET["nombre"];
$fechaInicio=$_GET["fechaInicio"];
$fechaFin=$_GET["fechaFin"];

$sql = "SELECT * FROM sensadoP 
WHERE (hora >= '{$fechaInicio}' and hora <='{$fechaFin}') and id_panel = (SELECT id_panel FROM panel_solar WHERE nombre LIKE '{$nombre}')
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
