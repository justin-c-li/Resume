# File name: test.py
# Author: Justin Li

import MySQLdb
import sys

#updates the mailing_logs table
def update_logs():
	#deletes the entries on the current day to prevent duplicates
	cursor.execute('DELETE FROM mailing_logs WHERE time=CURDATE()')

	#Adds the data entries from the mailing to the mailing_logs table
	for n in range(0, len(email)):
		cursor.execute('INSERT INTO mailing_logs (domain, count, time) VALUES (%s,%s, CURDATE())',(email[n],count[n]))	
			

#made it all the domains only have 1 for simplicity
def prev_logs():
	#deletes the entries 30 days ago to prevent duplicates entries
	cursor.execute('DELETE FROM mailing_logs WHERE time=date_sub(CURDATE(),interval 30 day)')
	
	#Adds the data entries from the mailing to the mailing_logs table
	temp=1;
	for n in range(0, len(email)):
		cursor.execute('INSERT INTO mailing_logs (domain, count, time) VALUES (%s,%s, date_sub(CURDATE(),interval 30 day))',(email[n],temp))	
		
def compare_logs():
	current_email=[];
	prev_email=[];
	result_email=[];
	current_count=[];
	prev_count=[];
	result_count=[];
	
	print
	print 'Current Entries:'
	cursor.execute('SELECT domain, count, time FROM mailing_logs WHERE time=CURDATE()')
	for row in cursor.fetchall():
		current_email.append(row[0])
		current_count.append(row[1])
		print row[0],
		print row[1]
	
	print
	print 'Previous Entries from a month ago:'
	cursor.execute('SELECT domain, count, time FROM mailing_logs WHERE time=date_sub(CURDATE(),interval 30 day)')
	for row in cursor.fetchall():
		prev_email.append(row[0])
		prev_count.append(row[1])
		print row[0],
		print row[1]
	
	#Used current_email since new domains may be added in the present
	for a in range(0,len(current_email)):
		found=0;
		#subtracting founded to make sure it doesn't go out of bound as the list shrinks for the prev one
		for b in range(0,len(prev_email)): #since length is used it should re-adjuct itself automatically as the list shrinks
			if(current_email[a]==prev_email[b]):
				result_email.append(current_email[a])
				result_count.append(100*(current_count[a]-prev_count[b])/prev_count[b])
				#removing the entries that were already matched up to reduce the search size since they are no longer needed
				del prev_email[b] #used del instead of .remove since that would have to search through the list which would be more inefficient
				del prev_count[b]
				found=1;
				break #skips searching the rest of the list since it's already found
			#Incase the domain didn't exist in the past
		if(found==0):
			result_count[a]=current_count[a]
			result_email[a]=current_email[a]
	
	
	point=0; #keeps track of the top lists
	top_result=[None]*50;
	top_domain=[None]*50;
	#this is coded for if they're is a large very database to reduce the search
	for a in range(0,len(result_email)):
		if(top_result[point]<result_count[a]):
			top_result[point]=result_count[a]
			top_domain[point]=result_email[a]
			point+=1 #increments the pointer so that it moves on to the next smallest number in the list
		#resets the point to the smallest number in the list so that it always compares to the smallest first
		if(point>49):
			point=0
			#Finds the smallest count in every loop and puts it infront
			for i in range (0,50-1):
				if(top_result[i]==None):
					break
				for j in range(0,50):
					if(top_result[j]==None):
						break
					if(top_result[i]<top_result[j]):
						temp=top_domain[i]
						top_domain[i]=top_domain[j]
						top_domain[j]=temp
						
						temp=top_result[i]
						top_result[i]=top_result[j]
						top_result[j]=temp
			
	#now sorts through the top 50 only
	for i in range (0,50-1):
		if(top_result[i]==None):
			break
		for j in range(0,i):
			if(top_result[j]==None):
				break
			if(top_result[i]>top_result[j]):
				temp=top_domain[i]
				top_domain[i]=top_domain[j]
				top_domain[j]=temp
						
				temp=top_result[i]
				top_result[i]=top_result[j]
				top_result[j]=temp
				
	print
	print 'Final Results for the top Domains:'
	for i in range(0,len(result_email)):
		if(top_result[i]==None): #prevents the loop from outputing empty entries
			break
		print top_domain[i],
		print top_result[i],
		print '%'
	print
	
def clear_logs():
	cursor.execute('DELETE FROM mailing_logs WHERE time!=0')

try:
	db=MySQLdb.connect(host='localhost', user='root',passwd='pass',db='test');

except Exception as e:
	sys.exit('ERROR cannot access database')
	
cursor = db.cursor()
cursor.execute('SELECT domain, COUNT(*) FROM mailing GROUP BY domain')

#stores the data in a temporary array
email=[];
count=[];
for row in cursor.fetchall():
	email.append(row[0])
	count.append(row[1])

		
#clear_logs();
prev_logs();
update_logs();
compare_logs();

db.commit()
db.close()
