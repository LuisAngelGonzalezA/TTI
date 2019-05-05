<?php

include("conexion.php");

$id=$_GET["id_bateria"];

	$sql = "SELECT * FROM bateria WHERE id_bateria='{$id}'";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	if($sql){

		$operacion["operacion"] = '1';
		$json['datos'][] = $operacion;
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		

		mysqli_close($conn);
		echo json_encode($json);
	}

?>
