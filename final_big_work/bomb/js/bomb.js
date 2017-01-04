/// <reference path="jquery.min.js" />
var width=0;
var height=0;
var hard=0;
var flag=parseInt(0);
var a;
var bomb_num=0;
var bomb_cur=0;
var correct_bomb=0;
var on_going=0;
var visit=new Array();
console.log(a);

var app = new Vue({
				  el: '#record',
				  data: {
				    bomb_num: bomb_num,
				    bomb_cur: bomb_cur
				  }
			});
function init_visit(visit)
{
	for(var i=0;i<=height+1;i++)
	{
		visit[i]=new Array();
		for(var j=0;j<=width+1;j++)
		{
			visit[i][j]=0;

		}
	}
}

function Create_bomb(width_w,height_w,hard_w)
{
	a=[];
	var count=0;
	height=height_w;
	width=width_w;
	hard=hard_w;
	console.log(width,height,hard);
	init_visit(visit);
	for(var i=1;i<=height_w;i++)
	{
		a[i]=new Array();
		for(var j=1;j<=width_w;j++)
		{
			a[i][j]=Math.floor(Math.random()*(hard+1));
			if(a[i][j]==0)
			{
				a[i][j]=-1;
				count++;
			}
		}
	}
	console.log(count);
	a[0]=new Array();
	a[height+1]=new Array();
	for(var i=0;i<=height_w;i++)
	{
		 a[i][0]=0;
		a[i][(width_w+1)]=0;
	}
	for(var j=0;j<=width_w+1;j++)
	{
		a[0][j]=0;
		a[height+1][j]=0;
	}
	console.log(a);
	app.bomb_cur=0;
	app.bomb_num=0;
	return a;
}
function Count_bomb(a,x,y,x1,y1)
{
	var count=0;
	for(var i=0;i<8;i++)
	{
		if(a[x1+x[i]][y1+y[i]]<0)
			count++;
	}
	return count;
}
function random_start(a,x1,y1)
{
	var y=[-1,0,1,1,1,0,-1,-1];//start form left above
	var x=[1,1,1,0,-1,-1,-1,0];
	for(var i=0;i<x.length;i++)
	{
		a[x1+x[i]][y1+y[i]]=1;
	}
	a[x1][y1]=1;
	var max_x=Math.floor(Math.random()*(width/2));
	var max_y=Math.floor(Math.random()*(height/2));
	for(var i=Math.abs(x1-max_x);i<(Math.abs(x1-max_x)+x1);i++)
	{
		for(var j=Math.abs(y1-max_y);j<(Math.abs(y1-max_y)+x1);j++)
		{
			if(a[i][j]<0)
				a[i][j]=Math.floor(Math.random()*(hard+1))-(6-hard);
		}
	}
	return a;
}
function init_map(a,width,height)
{
	var x=[-1,0,1,1,1,0,-1,-1];//start form left above
	var y=[1,1,1,0,-1,-1,-1,0];
	var tmp;
	bomb_num=0;
	for(var i=1;i<=height;i++)
	{
		for(var j=1;j<=width;j++)
		{
			if(a[i][j]>=0)
			{
				a[i][j]=Count_bomb(a,x,y,i,j);
			}
			else
			{
				bomb_num++;
			}
		}
	}
	app.bomb_num=bomb_num;
	app.bomb_cur=0;
}
function get_matrix()
{
	var a=Create_bomb(20,20);
	init_map(a,20,20);
	console.log(a);
	return a;
}
function show_num(x,y,a)
{
	var c;
	c=(x-1)*width+y;
	console.log(c);
	$(`input[id=${c}]`).removeClass("default");
	$(`input[id=${c}]`).addClass("flag");
	$(`input[id=${c}]`).val(`${a[x][y]}`);
	
}
function left_click(a,p_x,p_y)
{
	//check if it is a bomb
	if(a[p_x][p_y]<0)
	{
		alert("bomb  loser!");
	}
	else if(a[p_x][p_y]>0)
	{
		var c;
		c=(p_x-1)*width+p_y;
		console.log(c);
		show_num(p_x,p_y,a);
		visit[p_x][p_y]=1;
	}
	else
	{
		var q=new Array();
		var ob;
		var y=[-1,0,1,1,1,0,-1,-1];//start form left above//列
		var x=[1,1,1,0,-1,-1,-1,0];//行 
		var next_x,next_y;
		q.unshift({x:p_x,y:p_y});
	//	show_num(p_x,p_y,a);
		while(q.length)
		{
			ob=q.pop();
			show_num(ob.x,ob.y,a);
			if(a[ob.x][ob.y]==0)
			{				
				console.log("ori:",ob.x,ob.y);
				for(var i=0;i<x.length;i++)
				{
					var new_x,new_y;
					new_x=ob.x+x[i];
					new_y=ob.y+y[i];
					
					console.log("x:",ob.x,"y:",ob.y,"new_x:",new_x,"new_y:",new_y,"width:",width,"height:",height);
					
					
					if(new_x>0&&new_x<=height&&new_y>0&&new_y<=width)
					{
						console.log("yes",new_x,new_y,'p');
						if(a[new_x][new_y]>=0)
						{
							show_num(new_x,new_y,a);
								//show_num(new_x,new_y,a);
								
							console.log(new_x,new_y,a[new_x][new_y],visit[new_x][new_y]);
							if((a[new_x][new_y]==0)&&(visit[new_x][new_y]==0))
								q.unshift({x:new_x,y:new_y});
							console.log(" q.length: "+q.length);
							visit[new_x][new_y]=1;
						}
					}

				}
			}
		}
	}
}
function right_click(a,x,y)
{
	var c;
	c=(x-1)*width+y;
	console.log(c);
	if($(`input[id=${c}]`).hasClass("bomb_flag"))
	{
		$(`input[id=${c}]`).removeClass("bomb_flag");
		$(`input[id=${c}]`).addClass("default");
		bomb_cur--;
		if(a[x][y]<0)
		{
			correct_bomb--;
		}
	}
	else
	{
			$(`input[id=${c}]`).removeClass("default");
			$(`input[id=${c}]`).addClass("bomb_flag");

			bomb_cur++;
			if(a[x][y]<0)
				correct_bomb++;
	}
	if(bomb_cur==bomb_num&&bomb_num==correct_bomb)
		alert("Congradulation!!!!!");
}
function check_bomb(id)
{
	var e=window.event;
	var j=id%width;
	if(j==0)
		j=width;
	var i=(id-j)/width+1;//i行j列
	if(e.which==3)
		console.log("rigth");
	console.log("click: "+e.which);
	console.log(i+" "+j);
	visit[i][j]=1;
	if(flag==1)
	{
		console.log('bomb');
		if(a[i][j]<0)
		//	alert("bomb");
		console.log(a);
		console.log(i+" "+j);
		if(e.which==1)
			left_click(a,i,j);
		else if(e.which==3)
			right_click(a,i,j);
	}else{
		console.log('init');
		bomb_cur=0;
		a=random_start(a,i,j);
		init_map(a,width,height);
		left_click(a,i,j);
		flag=1;
	}
	app.bomb_cur=bomb_cur;

//	$('#record').show();

}
function re_start()
{
	flag=0;
	on_going=0;
	correct_bomb=0;
	$('#bg').empty();
	$('#record').hide();
	$('#re_start').hide();
	$('#ask_height_width').show();
	console.log('p');
}
function start()
{

	if(on_going==0)
	{		
	
		console.log("start");
	    var flag=0;
		var text='';
		var width=$('#width').val();
		var height=$('#height').val();
		var hard=$('#hard').val();
		if($.trim(width)==''||$.trim(height)==''||$.trim(hard)=='')
		{
			alert('请输入雷阵的宽和高和难度');
		}
		else
		{
			height=parseInt(height);
			width=parseInt(width);
			hard=parseInt(hard);
			var a=Create_bomb(width,height,hard);
			on_going=1;
			console.log(a);

			var count =0;
			for(var i=1;i<=height;i++)
			{
				for(var j=1;j<=width;j++)
				{
					count++;
					text+=`<input type="button" class="default" value=" "  name="${count}" id="${count}" onmousedown="check_bomb(this.id)">`;
				}
				text+=`</br>`;
			}
			$('#bg').append(text);
			$('#record').show();
			$('#re_start').show();
			$('#ask_height_width').hide();
		}
	}
}