#include "IModel.h"

//---------------------------------------------------------------------
IModel::IModel(const std::string &sName, unsigned dim)
  :m_dim(dim)
{}

//---------------------------------------------------------------------
unsigned IModel::GetDim() const
{
    return m_dim;
}

//---------------------------------------------------------------------
std::string IModel::GetName() const
{
    return m_sName;
}
