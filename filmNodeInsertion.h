#ifndef FILMNODEINSERTION_H_
#define FILMNODEINSERTION_H_

#include "../helpers.h"
#include "BST.h"
TreeNode* insertNodeByYear(TreeNode* head, TreeNode* const newFilm, int year); // DB initialization

TreeNode* insertNodeByRating(TreeNode* head, TreeNode* const newFilm, float rating); // DB initialization

TreeNode* insertNodeByTitle(TreeNode* head, TreeNode* newFilm, char* const title); // DB initialization
#endif // FILMNODEINSERTION_H_
