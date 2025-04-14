import google.generativeai as genai
import sys

def getSongs(info):
    genai.configure(api_key="AIzaSyBakuPnIa9RO3cCQoZVvoJh846zjhCuVVE") # make env

    model = genai.GenerativeModel('gemini-2.0-flash')

    prompt = f'''
    Give me 30 similar songs to the following list of songs
    {info}
    
    '''
    response = model.generate_content(prompt)

    return response.text


if __name__ == "__main__":
    data = sys.argv[1]
    print(getSongs(data))