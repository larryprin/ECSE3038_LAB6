from datetime import datetime
import os
from fastapi import FastAPI, Body, Request, HTTPException, status
from fastapi.responses import Response, JSONResponse
import pydantic
from pydantic import BaseModel, Field, EmailStr
from fastapi.encoders import jsonable_encoder
from fastapi.middleware.cors import CORSMiddleware
from bson import ObjectId
from typing import Optional, List
import motor.motor_asyncio
import json
import requests

app = FastAPI()
origins = [


]

app.add_middleware(
  CORSMiddleware,
  allow_origins = origins,
  allow_credentials = True,
  allow_methods = ["*"],
  allow_headers = ["*"],
)


client = motor.motor_asyncio.AsyncIOMotorClient("mongodb+srv://ecsebot:iYlk9QaJ9HpGjFhJ@cluster0.ntysecb.mongodb.net/?retryWrites=true&w=majority")
db = client.tank

temperature = ...
sunset_time_str = origins.json()
sunset_time = datetime.datetime.strptime(sunset_time_str, "%I:%M:%S %p").time()
now = datetime.datetime.now().time()
light_on = now > sunset_time
fan_on = temperature >= 28.0
pydantic.json.ENCODERS_BY_TYPE[ObjectId]=str


@app.get("/api/state", status_code=201)
async def wats_the_fan():
  fan1 = await db["fan"].find_one()

  if fan_on == True :
   fan1 = {
    "fan": fan_on
  }
  else:
    fan1 = {
      "fan": "off"
    }  
  return  fan1

@app.get("/api/state", status_code=201)
async def wats_the_light():
  light1 = await db["fan"].find_one()

  if light_on == True :
   light1 = {
    "light": light_on
  }
  else:
    light1 = {
      "light": "off"
    } 
  return  light1



@app.put("/api/state",status_code=201)
async def create_new(request: Request):
  new_object = await request.json()
  response = requests.get('https://ecse-sunset-api.onrender.com/api/sunset').json()
  sunset_time_str = response.json()["results"]["sunset"]
  sunset_time = datetime.datetime.strptime(sunset_time_str, "%I:%M:%S %p").time()
  return sunset_time

