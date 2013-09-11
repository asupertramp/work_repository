Select * into troommember_backup
from troommember
where curstate=1 or curstate=2 or curstate=3

select * from troommember where curstate=1 or curstate=2 or curstate=3 order by user_id

select  * from troommember_backup
select  * from troommember
select * from tuser

use Gsccs
if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1) drop table troommember_backup
update troommember set curstate =1  where id =1
update troommember set curstate =2  where id =12
update troommember set curstate =2  where id =11
update troommember set curstate =2  where id =10
update troommember set curstate =2  where id =7

update troommember set curstate =2  where id =8
update troommember set curstate =2  where id =9


update troommember_backup set curstate =1 where id =1
update troommember_backup set curstate =2 where id =4

if exists (select 1 from troommember_backup ) 
drop table troommember_backup

if exists (select 1 from troommember_backup) drop table troommember_backup
if  exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1) drop table troommember_backup  select top 0 * into troommember_backup from troommember

drop table troommember_backup

select top 0 * into troommember_backup from troommember

set IDENTITY_INSERT troommember_backup on INSERT INTO troommember_backup (id,membertype,room_id,user_id,curstate,begintime,endtime) SELECT id,membertype,room_id,user_id,curstate,begintime,endtime FROM troommember WHERE (curstate!=0) set IDENTITY_INSERT troommember_backup off

select  * into troommember_backup from troommember where curstate!=0

update troommember set curstate=0 where curstate=1 or curstate = 2

select distinct room_id  from troommember_backup

select * from troommember where curstate=1 or curstate=2 or curstate=3
drop table troommember_backup


if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1)
select * from troommember_backup

Select * into troommember_backup_temp
from troommember_backup
where curstate=1 or curstate=2 or curstate=3


if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1)
			             select distinct room_id from troommember_backup

delete  from troommember_backup
insert into troommember_backup select  from troommember where curstate!=0

if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1)
drop table troommember_backup

select   top   0   *   into   troommember_backup   from   troommember


INSERT INTO troommember_backup  
   (id,membertype,room_id,user_id,curstate,begintime,endtime)
SELECT id,membertype,room_id,user_id,curstate,begintime,endtime
FROM troommember
WHERE (curstate!=0)

if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1) 
select distinct room_id from troommember_backup

if exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1) drop table troommember_backup

select top 0 * into troommember_backup from troommember


if not exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1)   
select top 0 * into troommember_backup from troommember


if not exists (select * from sysobjects where objectproperty(object_id('troommember_backup'),'istable') = 1) select top 0 * into troommember_backup from troommember go

set IDENTITY_INSERT TRoommember on
insert into troommember (id,user_id,room_id,membertype,curstate)
values (12,3613994980,1,1,1)
set IDENTITY_INSERT TRoommember off

delete from tuser where id = 3
delete from troommember where user_id = 3638337508


set IDENTITY_INSERT TRoom on
insert into troom (id,floor,curstate)
values (5,0,1)
set IDENTITY_INSERT TRoom off

set IDENTITY_INSERT TUser on
insert into tuser (id,name )
values (3613994980,'¡ıÀŸ')
set IDENTITY_INSERT Tuser off

