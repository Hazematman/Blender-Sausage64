/***************************************************************
                             mesh.c
                             
Handles the parsing and creation of meshes
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "texture.h"
#include "mesh.h"


/*==============================
    add_mesh
    Creates a mesh object and adds it to the global list of meshes
    @param The name of the mesh
    @returns A pointer to the created mesh
==============================*/

s64Mesh* add_mesh(char* name)
{
    // Allocate memory for the mesh struct and string name
    s64Mesh* mesh = (s64Mesh*)calloc(1, sizeof(s64Mesh));
    if (mesh == NULL)
        terminate("Error: Unable to allocate memory for mesh object\n");
    mesh->name = (char*)calloc(strlen(name)+1, 1);
    if (mesh->name == NULL)
        terminate("Error: Unable to allocate memory for mesh name\n");
    
    // Store the data in the newly created mesh struct
    strcpy(mesh->name, name);
    
    // Add this mesh to our mesh list and return it
    list_append(&list_meshes, mesh);
    return mesh;
}


/*==============================
    add_vertex
    Creates a vertex object and adds it to a mesh's list of vertices
    @param A pointer to the mesh
    @returns A pointer to the created vertex
==============================*/

s64Vert* add_vertex(s64Mesh* mesh)
{
    s64Vert* vert = (s64Vert*)calloc(1, sizeof(s64Vert));
    if (vert == NULL)
        terminate("Error: Unable to allocate memory for mesh vertex\n");
    list_append(&(mesh->verts), vert);
    return vert;
}


/*==============================
    add_face
    Creates a face object and adds it to a mesh's list of faces
    @param A pointer to the mesh
    @returns A pointer to the created face
==============================*/

s64Face* add_face(s64Mesh* mesh)
{
    s64Face* face = (s64Face*)calloc(1, sizeof(s64Face));
    if (face == NULL)
        terminate("Error: Unable to allocate memory for mesh face\n");
    list_append(&(mesh->faces), face);
    return face;
}


/*==============================
    find_mesh
    Searches through the list of meshes for a mesh with the specified name
    @param The mesh name
    @returns The requested s64Mesh, or NULL if none was found 
==============================*/

s64Mesh* find_mesh(char* name)
{
    listNode* meshnode;
    
    // Iterate through the mesh list
    for (meshnode = list_meshes.head; meshnode != NULL; meshnode = meshnode->next)
    {
        s64Mesh* mesh = (s64Mesh*)meshnode->data;
        
        // If the name matches, return the mesh struct pointer
        if (!strcmp(mesh->name, name))
            return mesh;
    }
    
    // No mesh found, return NULL
    return NULL;
}