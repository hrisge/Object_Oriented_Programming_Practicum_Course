#include "Market.hpp"

Market::Market() : items() {}

Market::~Market()
{
    for (Item& i : items) {
        delete i.product;
    }
}

const Array<Item>& Market::getItems() const
{
    return items;
}

void Market::addProduct(const Product& p)
{
    items.push_back(Item(new Product(p), 0));
}

void Market::removeProduct(const Product& p)
{
    items.remove_first([&](const Item& i) {return i.getProduct() == p; });
}

void Market::buyProduct(const Product& p, unsigned count)
{
    Array<Item>::iterator toBuy =
        items.findPos([&](const Item& i) {return i.getProduct() == p; });
    if (!toBuy) {
        throw std::invalid_argument("Product is not listed in the market");
    }
    else {
        (*toBuy).count += count;
    }
}

void Market::sellProduct(const Product& p, unsigned count)
{
    Array<Item>::iterator toSell =
        items.findPos([&](const Item& i) {return i.getProduct() == p; });
    if (!toSell) {
        throw std::invalid_argument("Product is not listed in the market");
    }
    else {
        if ((*toSell).count < count) {
            throw std::invalid_argument("Cannot lower with that amount");
        }
        (*toSell).count -= count;
    }
}

int Market::receivingTimeFor(const Product& p, unsigned count) const
{
    Array<Item>::const_iterator item =
        items.findPos([&](const Item& i) {return i.getProduct() == p; });
    if (!item) {
        throw std::invalid_argument("Product is not listed in the market");
    }
    else {
        return count > (*item).getCount() ?
            (*item).getProduct().getDelivery().getDeliveryTime() : 0;
    }
}
