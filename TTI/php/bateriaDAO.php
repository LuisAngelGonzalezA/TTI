<?php

include("conexion.php");

	$sql = "SELECT b.*, h.activo FROM bateria b, historial_bateria_panel h where  b.id_bateria = h.id_bateria and b.isEliminado=0 GROUP BY h.activo, b.nombre ORDER BY b.id_bateria, h.fecha";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	$operacion["operacion"] = '4';
	$json['datos'][] = $operacion;
	if($sql){
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		mysqli_close($conn);
		echo json_encode($json);
	}

?>
