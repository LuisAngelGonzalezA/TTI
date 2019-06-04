<?php

include("conexion.php");

	$sql = "SELECT * FROM bateria WHERE id_bateria = (SELECT id_bateria FROM sensadoB ORDER BY id_sensado_b DESC LIMIT 1)";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	$operacion["operacion"] = '8';
	$json['datos'][] = $operacion;
	if($sql){
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		mysqli_close($conn);
		echo json_encode($json);
	}

?>
