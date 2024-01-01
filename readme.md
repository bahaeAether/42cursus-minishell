<h1 align=center>
	<b> :rainbow: Minishell :rainbow: </b>
	<br>
</h1>

<h2 align=center>
	<b> The project that will break your soul and make your life miserable! </b>
	<br>
	<br>
	<h1 align=center>---------------<h1>

</h2>

<h3>
	<p>
		<u>If you want to clone this minishell and test it for youself do the following:</u>
		<br>
	</p>
</h3>

<div>
	<p class="text-left">	<b>1\    </b> After cloning, if you dont have readline installed type in the following command: </p>
	
	
	make readline
 </div>

 <div>
	<p>	<b>2\    </b> go to ./parsing/parsing.h line 31, then change these two lines:</p>

 	# include "/Users/baboulou/readline/include/readline/readline.h"
	# include "/Users/baboulou/readline/include/readline/history.h"
 </div>

 <div>
	 with these two:

  	# include "(YOUR_HOME_PATH)/readline/include/readline/readline.h"
	# include "(YOUR_HOME_PATH)/readline/include/readline/history.h"
 </div>

 <div>
	(YOUR_HOME_PATH) being the absolute path to your home directory...
	<br>
	you can get that using the command:
	
	echo $HOME
 </div>

 <div>
	 <p>	<b>3\    </b>type: </p>

  	make
 </div>
 
 ---

<h4>
	now you should have an executable named ./minishell
	<br>
	Enjoy :)
</h4>

<br>

<div>
	you can test memory leaks using this command in another terminal:

 	bash leak_script.sh
</div>
