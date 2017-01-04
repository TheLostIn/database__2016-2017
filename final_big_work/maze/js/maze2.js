
/// <reference path="jquery.min.js" />

	var on_going=0;
	var width=0;
	var height=0;
	var hard=0;
	var flag=parseInt(0);
	var a;
	var count_visit=0;
	var correct_bomb=0;
	var visit=new Array();
	var father;
	var cur;
	var start_point;
	var end_point;
	var rank;
	var count;
	var record;
	/*
	var app = new Vue({
					  el: '#record',
					  data: {
					    bomb_num: bomb_num,
					    bomb_cur: bomb_cur
					  }
				});
				*/
	function init_visit(visit,flag)
	{
		visit = new Array();
		for(var i=0;i<=height+1;i++)
		{
			visit[i]=new Array();
			for(var j=0;j<=width+1;j++)
			{
				visit[i][j]=flag;
			}
		}
		return visit;
	}
	function init_rank(rank)
	{
		rank = new Array();
		for(var i=0;i<(height+1)*(width+1);i++)
		{
			rank[i]=1;
		}
		return rank;
	}

	function Create_init_maze(width_w,height_w,hard_w)
	{
		a=new Array();
		var count=0;
		height=height_w;
		width=width_w;
		hard=hard_w;
		console.log(width,height,hard);
		visit=new Array();
		visit = init_visit(visit,-1);
		console.log(visit);
		for(var i=1;i<=height_w;i++)
		{
			a[i]=new Array();
			if(i%2==0)
			{
				a[i][0]=-1;
				a[i][1]=-1;
				for(var j=2;j<=width_w;j+=2)
				{					
					a[i][j]=0;
					visit[i][j]=0;
					count++;
					a[i][j+1]=-1;
				}
			}
			else
			{
				for(var j=1;j<=width_w;j++)
				{
					a[i][j]=-1;
				}
			}
		}
		console.log(count);
		a[0]=new Array();
		a[height+1]=new Array();
		for(var i=0;i<=height_w;i++)
		{
			 a[i][0]=-1;
			a[i][(width_w+1)]=-1;
		}
		for(var j=0;j<=width_w+1;j++)
		{
			a[0][j]=-1;
			a[height+1][j]=-1;
		///	a[6][j]=-1;
		}
		console.log(a);
		count_visit=count;
		return a;
	}
	function pick_in_out()
	{
		var flag=1;
		var i=0;
		flag=Math.floor(Math.random()*2);
		if(flag)
		{
			var j;
			var down,up;
			j=Math.floor(Math.random()*width)+1;
			down = j%2==0?j:j+1;
			j=Math.floor(Math.random()*width)+1;
			up= j%2==0?j:j+1;
			start_point={x:height-1,y:down};
			end_point={x:2,y:up};
		}
		else
		{
			var j;
			var right,left;
			j=Math.floor(Math.random()*height)+1;
			left = j%2==0?j:j+1;
			j=Math.floor(Math.random()*height)+1;
			right= j%2==0?j:j+1;
			start_point={x:left,y:2};
			end_point={x:right,y:width-1};                      
		}
		cur=start_point;
		return {in:start_point,out:end_point};
	}
	function init_father(father_f)
	{
		father_f = new Array();
		for(var i=0;i<=(height+1)*(width+1);i++)
		{
			father_f[i]=i;
		}
		return father_f;
	}
	function find_father(x)
	{
		var root_r;
		root_r=x;
		while(father[root_r]!=root_r)
		{
			root_r=father[root_r];
		}
		while(root_r!=x)//查找的同时简化集合
		{
			var temp=father[x];
			father[x]=root_r;
			x=temp;
		}
	///	console.log(root_r);
		return root_r;
	}
	function Union_root(point_1,point_2)
	{
		var x=find_father(point_1);
		var y=find_father(point_2);
		console.log(x,y);
		if(x!=y)
		{
			if(rank[x]<=rank[y])
			{
				father[x]=y;
				rank[y]=rank[x]+rank[y];
			}
			else
			{
				father[y]=x;
				rank[x]=rank[x]+rank[y];
			}
		}
		console.log("union ："+x+" "+y,father[y],father[x]);
	}
	function point_to_count(i,j)
	{
		//console.log((i-1)*(width)+j);
		return (i-1)*(width)+j;

	}
	function has_way(cur_x,cur_y)
	{
		var x=[-2,0,2,0];
		var y=[0,2,0,-2];
		for(var i=0;i<x.length;i++)
		{
			new_x=cur_x+x[i];
			new_y=cur_y+y[i];
			if(new_x>0&&new_x<height&&new_y>0&&new_y<width)
			{
				if(visit[new_x][new_y]==0)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	function Union_make_maze(a,point)
	{
		var cc=0;

		console.log(point);
		start_point = point.in;
		end_point = point.out;
		var flag=0;
		var k;

		while(find_father(point_to_count(point.in.x,point.in.y))!=find_father(point_to_count(point.out.x,point.out.y)))
		{		
			console.log("first: "+find_father(point_to_count(point.in.x,point.in.y)),"second: "+find_father(point_to_count(point.out.x,point.out.y)));
			var cur_x = Math.floor(Math.random()*(height-2))+1;
			cur_x = cur_x%2==0?cur_x:(cur_x+1);
			var cur_y = Math.floor(Math.random()*(width-2))+1;
			cur_y = cur_y%2==0?cur_y:(cur_y+1);
			cc++;
			if(cc>2000)
			{
				return 0;
			}
			console.log("cur_x: "+cur_x,"cur_y: "+cur_y);
		//	var  j=prompt("pp");
			var x=[-2,0,2,0];
			var y=[0,2,0,-2];
			var x_1=[-1,0,1,0];
			var y_1=[0,1,0,-1];
			var tmp=Math.floor(Math.random()*4);
			var new_x,new_y;

			console.log("cur_x: "+cur_x,"cur_y: "+cur_y,"tmp: "+tmp);
			new_x=cur_x+x[tmp];
			new_y=cur_y+y[tmp];
			console.log(cc);
			if(new_x>0&&new_x<height&&new_y>0&&new_y<width)
			{
				if(a[new_x][new_y]==0&&a[cur_x][cur_y]==0)
				{
					console.log("1 find_fa: cur:  "+find_father(point_to_count(cur_x,cur_y))+"find_fa cur :  "+find_father(point_to_count(new_x,new_y)));
					if(find_father(point_to_count(cur_x,cur_y))!=find_father(point_to_count(new_x,new_y)))
					{
						console.log("2 find_fa: cur:  "+find_father(point_to_count(cur_x,cur_y))+"find_fa cur :  "+find_father(point_to_count(new_x,new_y)));
					
						Union_root(point_to_count(new_x,new_y),point_to_count(cur_x,cur_y));
						a[cur_x+x_1[tmp]][cur_y+y_1[tmp]]=0;
						console.log(cur_x,cur_y,new_x,new_y,cur_x+x_1[tmp],cur_y+y_1[tmp]);
						console.log(a);
					}
				}
			}
		}
		//console.log("final: ",cur_x,cur_y,new_x,new_y,cur_x+x_1[tmp],cur_y+y_1[tmp]);
		console.log(a);
		return 1;

	} 
function back_place(num,type="normal")
{
	//setTimeout($(`input[id=${num}]`).removeClass("walk"), 3000);
	//setTimeout($(`input[id=${num}]`).addClass("default"), 3000);
	if(type=="help")
	{
		$(`input[id=${num}]`).removeClass("help");
	}
	else
	{
		$(`input[id=${num}]`).removeClass("walk");
	}
	$(`input[id=${num}]`).addClass("default");
}
function show_place(num,index,type="normal")
{
//	$(`input[id=${num}]`).val(index);
	//console.log("index: "+index);
	//setTimeout($(`input[id=${num}]`).removeClass("default"), 3000);
	//setTimeout($(`input[id=${num}]`).addClass("walk"), 3000);
	if(type=="help")
	{
		$(`input[id=${num}]`).addClass("help");
	}
	else
	{
		$(`input[id=${num}]`).addClass("walk");
	}
	$(`input[id=${num}]`).removeClass("default");
	//$(`input[id=${num}]`).addClass("walk");
}
function hello()
{
	console.log("hello");
}
function DFS_search(cur)
{

	var x=[-1,0,1,0];
	var y=[0,1,0,-1];
	var p;
	var new_x,new_y;
	var flag=1;
	var index=0;
	var st=new Array();
	record=new Array();
	console.log(cur);
	st.push(cur);
	console.log("st: "+st);
	p=cur;
	var i;
	visit[p.x][p.y]=1;
	while(((p.x!=end_point.x)||(p.y!=end_point.y))&&st.length)
	{
	//	setTimeout("console.log('pp')",5000);
			if(flag==0)
			{
				//if((p.x!=end_point.x)||(p.y!=end_point.y))
				//setTimeout(back_place(point_to_count(p.x,p.y)), 10000);
				//back_place(point_to_count(p.x,p.y));
				record.push({point:point_to_count(p.x,p.y),todo:"pop"});
				console.log(st);
				p=st.pop();
				//record.push({point:point_to_count(p.x,p.y),todo:"pop"});
				console.log("pop(): "+point_to_count(p.x,p.y));
			}
			
			flag=0;
			console.log("index: "+index+" point_to_count(p.x,p.y) : "+point_to_count(p.x,p.y));
			//console.log(point_to_count(p.x,p.y));
			console.log("p.x: "+p.x+" p.y: "+p.y+" i : "+i);
			for(i=0;i<x.length&&!flag;i++)
			{
				new_x=p.x+x[i];
				new_y=p.y+y[i];
				console.log("new_x: "+new_x+" new_y: "+new_y+" i : "+i);
				if(new_x>0&&new_x<height&&new_y>0&&new_y<width)
				{
					//console.log("visit: "+visit[new_x][new_y]);
				//	console.log("st.length: "+st.length);
					if(a[new_x][new_y]==0&&(visit[new_x][new_y]==0))
					{
						flag=1;
						//st.push(p);
						st.push({x:p.x,y:p.y});
						//setTimeout(show_place(point_to_count(p.x,p.y),index++), 10000);
						//show_place(point_to_count(p.x,p.y),index++);
						//record.push({point:point_to_count(p.x,p.y),todo:"push",index:index++});
						record.push({point:point_to_count(new_x,new_y),todo:"push",index:index++});
						visit[new_x][new_y]=1;
						p={x:new_x,y:new_y};
					//	console.log(visit);
						//break;
					}
				}
			}
	}
	console.log(a);
	//console.log(st);
}
function make_maze(w,h)
{	
	var c=0;
	c++;
	var flag=0;
	var point;	
	var d;

//	var w=$('#weight').val();
//	var h=$('#width').val();
	if(w==''||h=='')
	{
		alert('Please fill the blank.');
		return ;
	}
	while(!flag)
	{
		d=Create_init_maze(w,h,5);
		father=init_father(father);
		rank=init_rank(rank);
		point=pick_in_out();
		flag=Union_make_maze(d,point);
		console.log(a);
		console.log("flag: "+flag);
	}
	a=d;
	console.log(c);
	console.log(d);
	var text='';
	var class_type;
	var count=0;
	for(var i=1;i<=height;i++)
	{
		for(var j=1;j<=width;j++)
		{
			class_type= d[i][j]==0?"default":"block";
			count++;
			text+=`<input type="button" class="${class_type}" value=""  name="${count}" id="${count}" onmousedown="check_bomb(this.id)">`;
		}
		text+=`</br>`;
	}
	console.log(point);
	console.log(point_to_count(point.in.x,point.in.y));
	console.log(point_to_count(point.out.x,point.out.y));
	$('#bg').append(text);
	$(`input[id=${point_to_count(point.in.x,point.in.y)}]`).removeClass("default");
	$(`input[id=${point_to_count(point.in.x,point.in.y)}]`).addClass("in");

	$(`input[id=${point_to_count(point.out.x,point.out.y)}]`).removeClass("default");
	$(`input[id=${point_to_count(point.out.x,point.out.y)}]`).addClass("out");

	$('#re_start').show();
	$('#help').show();
	$('#ask_height_width').hide();
}
function key_event()
{
	var cur_x=cur.x;
	var cur_y=cur.y;
	var x=[-1,0,1,0];
	var y=[0,1,0,-1];
	visit=init_visit(visit,0);
	visit[cur_x][cur_y]=1;
	var key=[38,39,40,37];
	 document.onkeydown=function(event){
	 	var new_x,new_y;
            var e = event || window.event || arguments.callee.caller.arguments[0];
            if(e)
            {
             	for(var i=0;i<4;i++)
             	{
	         		if(e.keyCode==key[i])
	         		{  
	                 //要做的事情
		                 new_x=cur_x+x[i];
		                 new_y=cur_y+y[i];
		                 if(new_x>1&&new_x<height&&new_y>1&&new_y<width)
		                 {
		                 	if(a[new_x][new_y]==0)
		                 	{
			                 	if(visit[new_x][new_y]==0)
			                 	{
			                 		show_place(point_to_count(new_x,new_y),0);
			                 		cur_x=new_x;
			                 		cur_y=new_y;
			                 		visit[new_x][new_y]=1;
			                 	}
			                 	else if(visit[new_x][new_y]==1)
			                 	{
			                 		back_place(point_to_count(cur_x,cur_y));
			                 		visit[cur_x][cur_y]=0;
			                 		cur_x=new_x;
			                 		cur_y=new_y;
			                 	}		            
		                 	}
		                 }
		                if(cur_x==end_point.x&&cur_y==end_point.y)
		             	{
		             		alert('Congradulations!!');
		             		re_start();
		             	}
		                return false;
		                break;
	                }
             	}
             
            }
         }; 
}
function make()
{
	if(on_going==0)
	{
		if($('#height').val()==''||$('#width').val()=='')
		{
			console.log('pp');
			alert('please complete the height and width.');
		}
		else
		{
			var h=$('#height').val();
			var w=$('#width').val();
			console.log(h,w);
			w=parseInt(w);
			h=parseInt(h);      
			if(w%2==0||h%2==0)
			{
				alert("请输入奇数!");
			}
			else
			{
				on_going=1;
				console.log(w+1,h+2);
				make_maze(w,h);
				key_event();
			}
			
		}
	}
}
function show_path()
{
	var p;
	var show = setInterval(function(){
		p=record.shift();
		console.log(p);
		console.log('a',p.index);
		if(p.todo=="push")
		{
			
			setTimeout(show_place, 500, p.point, p.index,"help");
			console.log('b',p.index);
		}	　 		
		else
		{
			setTimeout(back_place, 500, p.point,"help");
		}
		console.log('c');
		if(record.length==0)
		{
			clearInterval(show);
		}
		}, 500);
	
}
function help()
{
	visit=init_visit(visit,0);
	console.log(visit);
	DFS_search(cur);
	show_path();
}
function re_start()
{
	flag=0;
	on_going=0;
	$('#bg').empty();
	$('#help').hide();
	$('#re_start').hide();
	$('#ask_height_width').show();
}