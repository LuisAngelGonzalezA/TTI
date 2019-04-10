select*from sensadoP where now() between hora and DATE_ADD(NOW(),INTERVAL 1 MINUTE) order by hora desc limit 1;


select hora ,now(),DATE_ADD(NOW(),INTERVAL 1 MINUTE) from sensadoP where now() between hora and (NOW() - INTERVAL 1 MINUTE) order by hora desc limit 1;

select hora ,now(),DATE_ADD(NOW(),INTERVAL 1 MINUTE) from sensadoP where hora between (NOW() - INTERVAL 0 MINUTE)  and (NOW() - INTERVAL 1 MINUTE) order by hora desc limit 1;




select *,now()from sensadoP where hora between (now() -INTERVAL 30 SECOND) and (now()) order by hora limit 1;





 
select now(),(now()-INTERVAL 1 MINUTE);

select*from sensadoP where hora >= DATE_ADD(NOW(),INTERVAL 30 SECOND) order by hora desc limit 1;


select DATE_ADD(NOW(),INTERVAL 30 SECOND); 
