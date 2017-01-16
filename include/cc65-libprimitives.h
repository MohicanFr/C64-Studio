/*****************************************************************************/
/*                            Primitives Library                             */
/*****************************************************************************/

#include "cc65-libmemory.h"

const char* CreateBox(int *nVerts, int *nTris, fix8 **verts, fix8 **norms, int **tris, int **pxls)
{
	static char name[] = "Box";
	int v = 0;
	int t = 0;
		
	// Allocate memory for triangles/normals/vertices
	(*nTris) = 12;
	(*nVerts) = 8;
	MallocInt(tris, (*nTris)*3);
	MallocFix8(norms, (*nTris)*3);
	MallocFix8(verts, (*nVerts)*6);

	// Allocate pixel data in main memory (for fast drawing)
	(*pxls) = (int*) malloc ((*nVerts)*2*sizeof(int));
	
	// Generate triangles
	WriteInt(tris, t++, 0);
	WriteInt(tris, t++, 1);
	WriteInt(tris, t++, 2);
	
	WriteInt(tris, t++, 0);
	WriteInt(tris, t++, 2);
	WriteInt(tris, t++, 3);

	WriteInt(tris, t++, 0);
	WriteInt(tris, t++, 5);
	WriteInt(tris, t++, 1);

	WriteInt(tris, t++, 0);
	WriteInt(tris, t++, 4);
	WriteInt(tris, t++, 5);

	WriteInt(tris, t++, 4);
	WriteInt(tris, t++, 6);
	WriteInt(tris, t++, 5);

	WriteInt(tris, t++, 4);
	WriteInt(tris, t++, 7);
	WriteInt(tris, t++, 6);

	WriteInt(tris, t++, 3);
	WriteInt(tris, t++, 2);
	WriteInt(tris, t++, 6);

	WriteInt(tris, t++, 3);
	WriteInt(tris, t++, 6);
	WriteInt(tris, t++, 7);
	
	WriteInt(tris, t++, 3);
	WriteInt(tris, t++, 4);
	WriteInt(tris, t++, 0);

	WriteInt(tris, t++, 3);
	WriteInt(tris, t++, 7);
	WriteInt(tris, t++, 4);

	WriteInt(tris, t++, 1);
	WriteInt(tris, t++, 5);
	WriteInt(tris, t++, 2);

	WriteInt(tris, t++, 2);
	WriteInt(tris, t++, 5);
	WriteInt(tris, t++, 6);
	
	// Generate vertices
	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++, -128);
	v += 3;

	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++, -128);
	v += 3;

	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++, -128);
	v += 3;

	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++, -128);
	v += 3;

	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++,  128);
	v += 3;

	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++,  128);
	v += 3;

	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++,  128);
	v += 3;

	WriteFix8(verts, v++,  128);
	WriteFix8(verts, v++, -128);
	WriteFix8(verts, v++,  128);
	v += 3;
	
	return name;
} 

const char* CreateCylinder(int faces, int *nVerts, int *nTris, fix8 **verts, fix8 **norms, int **tris, int **pxls)
{
	static char name[] = "Cylinder";
	int v = 0;
	int t = 0;
	int i;
	
	// Allocate memory for triangles/normals/vertices
	(*nTris) = 4*faces;
	(*nVerts) = 2*(faces+1);
	MallocInt(tris, (*nTris)*3);
	MallocFix8(norms, (*nTris)*3);
	MallocFix8(verts, (*nVerts)*6);
	
	// Allocate pixel data in main memory (for fast drawing)
	(*pxls) = (int*) malloc ((*nVerts)*2*sizeof(int));
	
	// Generate vertices
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, -128);
	v += 3;

	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, 128);	
	v += 3;
	
	for (i = 0; i < faces; ++i) {
		// Generate vertices
		WriteFix8(verts, v++, cc65_cos((360*i)/faces)/2);
		WriteFix8(verts, v++, cc65_sin((360*i)/faces)/2);
		WriteFix8(verts, v++, -128);
		v += 3;

		WriteFix8(verts, v++, cc65_cos((360*i)/faces)/2);
		WriteFix8(verts, v++, cc65_sin((360*i)/faces)/2);
		WriteFix8(verts, v++, 128);
		v += 3;	
		
		// Generate bottom triangle
		WriteInt(tris, t++, 2*i+2);
		WriteInt(tris, t++, 0);
		if (i < (faces-1)) {
			WriteInt(tris, t++, 2*(i+1)+2);		
		} else {
			WriteInt(tris, t++, 2);			
		}
		
		// Generate side triangles
		WriteInt(tris, t++, 2*i+3);
		WriteInt(tris, t++, 2*i+2);
		if (i < (faces-1)) {
			WriteInt(tris, t++, 2*(i+1)+2);		
		} else {
			WriteInt(tris, t++, 2);			
		}		

		WriteInt(tris, t++, 2*i+3);		
		if (i < (faces-1)) {
			WriteInt(tris, t++, 2*(i+1)+2);
			WriteInt(tris, t++, 2*(i+1)+3);
		} else {
			WriteInt(tris, t++, 2);
			WriteInt(tris, t++, 3);
		}		
		
		// Generate top triangle
		WriteInt(tris, t++, 1);
		WriteInt(tris, t++, 2*i+3);
		if (i < (faces-1)) {
			WriteInt(tris, t++, 2*(i+1)+3);		
		} else {
			WriteInt(tris, t++, 3);			
		}		
	}
	
	return name;
}

const char* CreateSphere(int faces, int *nVerts, int *nTris, fix8 **verts, fix8 **norms, int **tris, int **pxls)
{
	static char name[] = "Sphere";
	fix8 x = 67;
	fix8 z = 109;
	int v = 0;
	int t = 0;
	
	// Allocate memory for triangles/normals/vertices
	if (faces <= 20) {
		(*nTris) = 20;
		(*nVerts) = 12;
	} else {
		(*nTris) = 60;
		(*nVerts) = 32;	
	}
	MallocInt(tris, (*nTris)*3);
	MallocFix8(norms, (*nTris)*3);
	MallocFix8(verts, (*nVerts)*6);

	// Allocate pixel data in main memory (for fast drawing)
	(*pxls) = (int*) malloc ((*nVerts)*2*sizeof(int));	
	
	// Generate triangles
	WriteInt(tris, t++, 0);	
	WriteInt(tris, t++, 4);	
	WriteInt(tris, t++, 1);	

	WriteInt(tris, t++, 0);	
	WriteInt(tris, t++, 9);	
	WriteInt(tris, t++, 4);	

	WriteInt(tris, t++, 9);	
	WriteInt(tris, t++, 5);	
	WriteInt(tris, t++, 4);	

	WriteInt(tris, t++, 4);	
	WriteInt(tris, t++, 5);	
	WriteInt(tris, t++, 8);	

	WriteInt(tris, t++, 4);	
	WriteInt(tris, t++, 8);	
	WriteInt(tris, t++, 1);		

	WriteInt(tris, t++, 8);	
	WriteInt(tris, t++, 10);	
	WriteInt(tris, t++, 1);		

	WriteInt(tris, t++, 8);	
	WriteInt(tris, t++, 3);	
	WriteInt(tris, t++, 10);		

	WriteInt(tris, t++, 5);	
	WriteInt(tris, t++, 3);	
	WriteInt(tris, t++, 8);		

	WriteInt(tris, t++, 5);	
	WriteInt(tris, t++, 2);	
	WriteInt(tris, t++, 3);		
	
	WriteInt(tris, t++, 2);	
	WriteInt(tris, t++, 7);	
	WriteInt(tris, t++, 3);		

	WriteInt(tris, t++, 7);	
	WriteInt(tris, t++, 10);	
	WriteInt(tris, t++, 3);		

	WriteInt(tris, t++, 7);	
	WriteInt(tris, t++, 6);	
	WriteInt(tris, t++, 10);		

	WriteInt(tris, t++, 7);	
	WriteInt(tris, t++, 11);	
	WriteInt(tris, t++, 6);		
	
	WriteInt(tris, t++, 11);	
	WriteInt(tris, t++, 0);	
	WriteInt(tris, t++, 6);		
	
	WriteInt(tris, t++, 0);	
	WriteInt(tris, t++, 1);	
	WriteInt(tris, t++, 6);		
	
	WriteInt(tris, t++, 6);	
	WriteInt(tris, t++, 1);	
	WriteInt(tris, t++, 10);		
	
	WriteInt(tris, t++, 9);	
	WriteInt(tris, t++, 0);	
	WriteInt(tris, t++, 11);		
	
	WriteInt(tris, t++, 9);	
	WriteInt(tris, t++, 11);	
	WriteInt(tris, t++, 2);		
	
	WriteInt(tris, t++, 9);	
	WriteInt(tris, t++, 2);	
	WriteInt(tris, t++, 5);		
	
	WriteInt(tris, t++, 7);	
	WriteInt(tris, t++, 2);	
	WriteInt(tris, t++, 11);
	
	// Generate vertices
	WriteFix8(verts, v++, -x);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, z);
	v += 3;

	WriteFix8(verts, v++, x);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, z);
	v += 3;
	
	WriteFix8(verts, v++, -x);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, -z);
	v += 3;

	WriteFix8(verts, v++, x);
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, -z);
	v += 3;

	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, z);
	WriteFix8(verts, v++, x);
	v += 3;

	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, z);
	WriteFix8(verts, v++, -x);
	v += 3;

	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, -z);
	WriteFix8(verts, v++, x);	
	v += 3;
	
	WriteFix8(verts, v++, 0);
	WriteFix8(verts, v++, -z);
	WriteFix8(verts, v++, -x);	
	v += 3;

	WriteFix8(verts, v++, z);
	WriteFix8(verts, v++, x);
	WriteFix8(verts, v++, 0);	
	v += 3;

	WriteFix8(verts, v++, -z);
	WriteFix8(verts, v++, x);
	WriteFix8(verts, v++, 0);	
	v += 3;

	WriteFix8(verts, v++, z);
	WriteFix8(verts, v++, -x);
	WriteFix8(verts, v++, 0);
	v += 3;

	WriteFix8(verts, v++, -z);
	WriteFix8(verts, v++, -x);
	WriteFix8(verts, v++, 0);
	v += 3;
		
	return name;
}
