/// <reference path="jquery.min.js" />

	var width=0;
	var height=0;
	var hard=0;
	var flag=parseInt(0);
	var a;
	var bomb_num=0;
	var bomb_cur=0;
	var correct_bomb=0;
	var visit=new Array();
	var father_left=new Array();
	var father_right=new Array();
	var father_up=new Array();
	var father_down=new Array();
	var cur;
	var start_point;
	var end_point;
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
	function search()
	{

	}
	function rand_from_to()
	{
		
	}
	function Create_maze(width_w,height_w,hard_w)
	{
		a=[];
		var count=0;
		height=height_w;
		width=width_w;
		hard=hard_w;
		console.log(width,height,hard);
		visit = init_visit(visit);
		console.log(visit);
		for(var i=1;i<=height_w;i++)
		{
			a[i]=new Array();
			for(var j=1;j<=width_w;j++)
			{
				a[i][j]=Math.floor(Math.random()*hard)-4;
				if(a[i][j]<0)
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

		return a;
	}
	function Create_init_maze(width_w,height_w,hard_w)
	{
		a=[];
		var count=0;
		height=height_w;
		width=width_w;
		hard=hard_w;
		console.log(width,height,hard);
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
		return a;
	}
	function DFS_make_maze(a)
	{
		

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
	function check_result(a)
	{
		//father_left  father_right
		//father_up    father_down
		var q=new Array();
		var flag=0;
		var y=[1,0,-1,0];
		var x=[0,1,0,-1];
		for(var i=0;i<=height+1;i++)
		{
			father_left[i]=-1;
			father_right[i]=-1;
		}
		for(var i=0;i<=width+1;i++)
		{
			father_up[i]=-1;
			father_down[i]=-1;
		}
		for(var i=1;i<=height;i++)//1列i行
		{
			if(a[i][1]>0&&visit[i][1]==0)
			{
				q.unshift({x:i,y:1});
				var tmp;
				visit[i][1]=1;
				while(q.length)
				{
					//console.log(i,1);
					tmp=q.pop();
					for(var j=0;j<x.length;j++)
					{
						var new_x=tmp.x+y[j];
						var new_y=tmp.y+x[j];
					//	console.log(new_x,new_y);
						if(new_x>0&&new_x<=height&&new_y>0&&new_y<=width)
						{
						//	console.log(new_x,new_y);
							if(a[new_x][new_y]>0&&visit[new_x][new_y]==0)
							{
							//	console.log(new_x,new_y);
								q.unshift({x:new_x,y:new_y});
								visit[new_x][new_y]=1;
								if((new_y)==1)
								{
									father_left[new_x]=i;
								}
								if((new_y)==width)
								{
									flag=1;
									father_right[new_x]=i;
									father_left[i]=i;
								}
							}	
						}
					}
				}
			}
		}
		visit=init_visit(visit);
		console.log(visit);
		for(var i=1;i<=width;i++)//1列i行
		{
			if(a[height][i]>0&&visit[height][i]==0)
			{
				q.unshift({x:height,y:i});
				var tmp;
				visit[height][i]=1;
				while(q.length)
				{
					tmp=q.pop();
					for(var j=0;j<x.length;j++)
					{
						var new_x=tmp.x+y[j];
						var new_y=tmp.y+x[j];
						if(new_x>0&&new_x<=height&&new_y>0&&new_y<=width)
						{
							if(a[new_x][new_y]>0&&visit[new_x][new_y]==0)
							{
								visit[new_x][new_y]=1;
								q.unshift({x:new_x,y:new_y});

								if((new_x)==height)
								{
									father_down[new_y]=i;
								}
								if((new_x)==1)
								{
									flag=1;
									father_up[new_y]=i;
									father_down[i]=i;
								}
							}	
						}
					}
				}
			}
		}
		console.log(a);
		console.log(father_up);
		console.log(father_down);
		console.log(father_left);
		console.log(father_right);
		return flag;
	}
	function check_re()
	{
		for(var i=1;i<=height;i++)
		{
			if(father_left[i]!=i&&father_left[i]!=-1)
			{
				if(father_left[father_left[i]]!=father_left[i])
				{
					father_left[i]=-1;
				}
			}
		}
		for(var i=1;i<=height;i++)
		{
			if(father_right[i]!=-1)
			{
				if(father_left[father_right[i]]!=father_right[i])
				{
					father_right[i]=-1;
				}
			}
		}
		for(var i=1;i<=width;i++)
		{
			if(father_down[i]!=i&&father_down[i]!=-1)
			{
				if(father_down[father_down[i]]!=father_down[i])
				{
					father_down[i]=-1;
				}
			}
		}
		for(var i=1;i<=width;i++)
		{	
			if(father_up[i]!=-1)
			{
				if(father_down[father_up[i]]!=father_up[i])
				{
					father_up[i]=-1;
				}
			}
		}
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
			while(father_down[j]==-1)
			{
				j=Math.floor(Math.random()*width)+1;
			}
			down = j;
			j=Math.floor(Math.random()*width)+1;
			while(father_up[j]==-1&&father_up[j]!=father_down[down])
			{
				j=Math.floor(Math.random()*width)+1;
			}
			up=j;
			start_point={x:height,y:down};
			end_point={x:1,y:up};
		}
		else
		{
			var j;
			var right,left;
			j=Math.floor(Math.random()*height)+1;
			while(father_left[j]==-1)
			{
				j=Math.floor(Math.random()*height)+1;
			}
			left = j;
			j=Math.floor(Math.random()*height)+1;
			while(father_left[j]==-1&&father_left[j]!=father_left[right])
			{
				j=Math.floor(Math.random()*height)+1;
			}
			right=j;
			start_point={x:left,y:1};
			end_point={x:right,y:width};                      
		}
		cur=start_point;
		return {in:start_point,out:end_point};
	}
	function re_start()
	{
		flag=0;
		$('#bg').empty();
		$('#record').hide();
		$('#re_start').hide();
		$('#ask_height_width').show();
		console.log('p');
	}
	function moveto(event)
	{
		// if(event.keyCode==13) location=bookpage;
  //     if(event.keyCode==37) location=prevpage;
  //     if(event.keyCode==39) location=nextpage;
      
      console.log(event.keyCode);
	}
// height=12;
// width=12;
// hard=5;
// console.log(father_up);
// console.log(father_down);
// console.log(father_left);
// console.log(father_right);
// // console.log(re);
// var d = Create_init_maze(13,13,5);
// console.log(visit);
//DFS_make_maze(d);