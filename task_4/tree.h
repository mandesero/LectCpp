#pragma once

#include <memory>

namespace NBinTree
{

    template <typename T>
    class TNode : public std::enable_shared_from_this<TNode<T>>
    {
    public:
        /*
        Использование наследования от класса std::enable_shared_from_this<TNode<T>>, дает возможность приведения this к shared_ptr или weak_ptr.
        Такой подход безопаснее, чем прямое приведение std::shared_ptr<TNode<T>>(this), поскольку при прямом приведении объект this может быть уничтожен несколько раз.
        Использование наследования от std::enable_shared_from_this позволяет создавать shared_ptr или weak_ptr,
        которые корректно отслеживают жизненный цикл объекта и предотвращают возможные ошибки, связанные с неправильным управлением памятью.
        */

        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
        using TNodeWeakPtr = std::weak_ptr<TNode<T>>;
        using TNodeConstWeakPtr = std::weak_ptr<const TNode<T>>;

        bool HasLeft() const
        {
            return Left;
        }

        bool HasRight() const
        {
            return Right;
        }

        bool HasParent() const
        {
            return Parent;
        }

        T &GetValue()
        {
            return Value;
        }

        const T &GetValue() const
        {
            return Value;
        }

        TNodePtr GetLeft()
        {
            return Left;
        }

        TNodeConstPtr GetLeft() const
        {
            return Left;
        }

        TNodePtr GetRight()
        {
            return Right;
        }

        TNodeConstPtr GetRight() const
        {
            return Right;
        }

        TNodePtr GetParent()
        {
            return Parent.expired() ? nullptr : Parent.lock();
        }

        TNodeConstPtr GetParent() const
        {
            return Parent.expired() ? nullptr : Parent.lock();
        }

        static TNodePtr CreateLeaf(T value)
        {
            return std::make_shared<TNode>(TNode(value));
        }

        static TNodePtr Fork(T value, TNodePtr left, TNodePtr right)
        {
            TNodePtr ptr = std::make_shared<TNode>(TNode(value, left, right));
            SetParent(ptr->GetLeft(), ptr);
            SetParent(ptr->GetRight(), ptr);
            return ptr;
        }

        TNodePtr ReplaceLeft(TNodePtr left)
        {
            /*
            Приведение к weak_ptr
            */ 
            SetParent(left, this->weak_from_this());
            SetParent(Left, TNodeWeakPtr());
            std::swap(left, Left);
            return left;
        }

        TNodePtr ReplaceRight(TNodePtr right)
        {
            /*
            Приведение к weak_ptr
            */ 
            SetParent(right, this->weak_from_this());
            SetParent(Right, TNodeWeakPtr());
            std::swap(right, Right);
            return right;
        }

        TNodePtr ReplaceRightWithLeaf(T value)
        {
            return ReplaceRight(CreateLeaf(value));
        }

        TNodePtr ReplaceLeftWithLeaf(T value)
        {
            return ReplaceLeft(CreateLeaf(value));
        }

        TNodePtr RemoveLeft()
        {
            return ReplaceLeft(nullptr);
        }

        TNodePtr RemoveRight()
        {
            return ReplaceRight(nullptr);
        }

    private:
        T Value;
        TNodePtr Left = nullptr;
        TNodePtr Right = nullptr;

        /*
        для прерывания цикла ссылок, нужно изменить тип Parent
        */
        TNodeWeakPtr Parent = TNodeWeakPtr();


        TNode(T value)
            : Value(value)
        {
        }

        TNode(T value, TNodePtr left, TNodePtr right)
            : 
            Value(value),
            Left(left ? left->shared_from_this() : TNodePtr{nullptr}),
            Right(right ? right->shared_from_this() : TNodePtr{nullptr})
        {
        }

        static void SetParent(TNodePtr node, TNodeWeakPtr parent)
        {
            if (node)
            {
                node->Parent = parent;
            }
        }
    };

} // namespace NBinTree