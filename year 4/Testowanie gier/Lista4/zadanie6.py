import pytest
from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.firefox.options import Options
import time
import os


options_firefox = Options()
options_firefox.binary_location = r'C:\Program Files\Mozilla Firefox\firefox.exe'


@pytest.fixture(params=['chrome', 'firefox'], scope='function')
def browser(request):
    if request.param == 'chrome':
        web_driver = webdriver.Chrome()
    if request.param == 'firefox':
        web_driver = webdriver.Firefox(options=options_firefox)
    yield web_driver
    web_driver.quit()


homepage = os.path.dirname(os.path.realpath(__file__)) + "\\page\\index.html"

fieldVals = [
    ('name','Sample name'), 
    ('surname','Sample surname'), 
    ('email','sample@example.com'),
    ('message', 'Testing message')]

def test_new_tab(browser):
    dir_path = os.path.dirname(os.path.realpath(__file__))
    browser.get(homepage);
    assert browser.title == "Home"
    browser.find_element_by_id('new_window_button').click()
    browser.switch_to.window(window_name=browser.window_handles[1])
    assert browser.title == "Home"
    assert len(browser.window_handles) == 2
    browser.close()

def test_fill_form(browser):
    browser.get(homepage)
    browser.find_element_by_link_text('Contact').click()

    for fieldName, fieldVal in fieldVals:
        field = browser.find_element_by_id(fieldName)
        field.send_keys(fieldVal)
        assert field.get_attribute('value') == fieldVal

    select = Select(browser.find_element_by_id('country'))
    select.select_by_visible_text('Germany')
    assert select.first_selected_option.text == 'Germany'

    browser.find_element_by_xpath("//input[@type='submit']").click()

    alert = browser.switch_to.alert
    assert alert.text == "Are you sure?"
    alert.accept()

def test_gallery(browser):
    browser.get(homepage)
    browser.find_element_by_link_text('Gallery').click()
    images = browser.find_elements_by_class_name("gallery")
    assert len(images) == 11