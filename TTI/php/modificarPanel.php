<?php

include("conexion.php");

$id=$_GET["id_panel"];
$operacion="1";
$nombre=$_GET["nombre"];
$voltajeMax=$_GET["voltajeMax"];
$corriente=$_GET["corriente"];
$isEliminado="0";
$json = array();

$sql = "UPDATE panel_solar SET id_mecanismo='{$operacion}', nombre='{$nombre}', voltaje_max='{$voltajeMax}', corriente_max='{$corriente}',isEliminado='{$isEliminado}' WHERE id_panel='{$id}'";

	
	if (mysqli_query($conn,$sql) === TRUE) {
		$result["operacion"] = '2';
		$json['datos'][] = $result;
	    echo json_encode($json);
	} else {
		$result["operacion"] = '2';
		$json['datos'][] = $conn->error;;
	    echo json_encode($json);
	}	

mysqli_close($conn);

?>
