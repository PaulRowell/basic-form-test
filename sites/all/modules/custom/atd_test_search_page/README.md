Task 2: Drupal method.
Simplier method, considered more for temp/"throw away" code. Should/Could be
expanded to extract the curl request into its own service (in doing so add
PHP Unit tests).

--Installation instructions--
Setup and install a basic Drupal env.
Enable the atd_test_search_page module
navigate to /product-search

1. Write 8-12 sentences explaining to another developer how you would a
approach building the product search below.

Depending on the business goals and KPIs, and the env/product the feature is
being developed into....
Create a page with a single title text search field (taking into account any
validation the form needs). Create a service that builds a call to the atd api
url with the needed parameters and settings.
Upon submission make a call to the atd api with the entered value as the title
search time (ensuring the input is filtered). Parse the returing json
(developing for possible errors and no results). Below the form show the
results in a table containing an image, title, and destination.
Considerations should be made for caching results, pagination, and allowing the
callback and results to be scalable.
