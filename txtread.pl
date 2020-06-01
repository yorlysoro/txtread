#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
use strict;
use warnings;
use Speech::eSpeak ':all';
menu();
sub menu
{
	my $opcion = 0;
	print "************************\n",
		  "*********MENU***********\n",
          "*1)Crear un archivo    *\n",
          "*2)Leer un archivo     *\n",
	      "*3)Modificar un archivo*\n",
	      "*4)Leer con espeak     *\n",
	      "*5)Salir               *\n",
	      "************************\n",
	      "************************\n";
	$opcion =<STDIN>;
	if($opcion == 1)
	{
		crear_archivo();
	}
	elsif($opcion == 2)
	{
		leer_archivo();
	}
	elsif($opcion == 3)
	{
		modificar_archivo();
	}
	elsif($opcion == 4)
	{
		leer_espeak();
	}
	elsif($opcion == 5)
	{
		print "Adios!\n";
		exit(1);
	}
	else
	{
		print "Error!\n";
		print "Elija una opcion\n\n";
		menu();
	}
	
	
}
sub crear_archivo
{
	my $nomarchivo;
	print "Introduzca el nombre del archivo\n";
	$nomarchivo = <STDIN>;
	open (ARCHIVO, ">>$nomarchivo") or die("Error al crear el archivo\n");
	print "Introduzca el contenido del archivo\n";
	print "(EOF al final para terminar)\n";
	my $alto = "EOF";
	my $contenido = " ";
	for(;$contenido ne $alto;)
	{
		$contenido = <STDIN>;
		chomp($contenido);
		if($contenido eq $alto){
			close(ARCHIVO);
			menu();
		}
		print ARCHIVO "$contenido\n";
		
	}
	
	
}

sub leer_archivo
{
	my $nomarchivo;
	my $pausa;
	print "Introduzca el nombre del archivo\n";
	$nomarchivo = <STDIN>;
	chomp($nomarchivo);
	open(ARCHIVO, "$nomarchivo");
	my @contenido = <ARCHIVO>;
	close(ARCHIVO);
	foreach my $lineas(@contenido)
	{
		chomp($lineas);
		print "$lineas\n";
	}
	$pausa = <STDIN>;
	while($pausa ne "\n") {}
	menu();
}
sub modificar_archivo
{
	my $nomarchivo;
	my $opcion = 0;
	print "************************\n",
          "*1)Borrar su contenido *\n",
          "*2)Dejar su contenido  *\n",
	      "*3)Volver al menu      *\n",
	      "************************\n",
	      "************************\n";
	$opcion = <STDIN>;
	if($opcion == 1)
	{
		print"Introduzca el nombre del archivo\n";
		$nomarchivo = <STDIN>;
		open(ARCHIVO, ">$nomarchivo") or die ("No se pudo abrir el archivo!");
		print "Introduzca el nuevo contenido\n";
		print "(EOF al final para terminar)\n";
		my $salto = "EOF";
		my $contenido = " ";
		for(;$contenido ne $salto;)
		{
			$contenido = <STDIN>;
			chomp($contenido);
			if($contenido eq $salto)
			{
				close(ARCHIVO);
				modificar_archivo();
			}
			print ARCHIVO "$contenido\n";
		}
	}
	elsif($opcion == 2)
	{
		print"Introduzca el nombre del archivo\n";
		$nomarchivo = <STDIN>;
		open(ARCHIVO, ">>$nomarchivo") or die ("No se pudo abrir el archivo!");
		print "Introduzca el contenido\n";
		print "(EOF al final para terminar)\n";
		my $salto = "EOF";
		my $contenido = " ";
		for(;$contenido ne $salto;)
		{
			$contenido = <STDIN>;
			chomp($contenido);
			if($contenido eq $salto)
			{
				close(ARCHIVO);
				modificar_archivo();
			}
			print ARCHIVO "$contenido\n";
		}
	}
	elsif($opcion == 3)
	{
		menu();
	}
}
sub leer_espeak
{
	my $speaker = Speech::eSpeak::new();
	$speaker->language("es");
	$speaker->volume(100);
	$speaker->rate(145);
	my $nomarchivo;
	my $pausa;
	print "Introduzca el nombre del archivo\n";
	$nomarchivo = <STDIN>;
	chomp($nomarchivo);
	open(ARCHIVO, "$nomarchivo");
	my @contenido = <ARCHIVO>;
	close(ARCHIVO);
	foreach my $lineas(@contenido)
	{
		chomp($lineas);
		print "$lineas\n";
		$speaker->speak(sprintf "$lineas\n");
	}
	$pausa = <STDIN>;
	while($pausa ne "\n") {}
	$speaker->stop();
	espeak_Terminate();
	menu();
}
