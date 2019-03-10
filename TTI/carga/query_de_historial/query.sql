--Consultas



select p.voltaje_max,b.voltaje_max from bateria b,panel_solar p,historial_bateria_panel hbp where
hbp.id_bateria=b.id_bateria and hbp.id_panel=p.id_panel and hbp.activo=1;



update historial_bateria_panel set activo=0 where activo=1;
